#include "Game/Public/Missile.h"
#include "Game/Public/MathHelper.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/DataManager.h"
#include "Game/Public/Target.h"

Missile::Missile(exEngineInterface* pEngine) : GameObject(pEngine)
{
	mSpeed = 60.0f;

	explosionSize = 40.0f;
	currentExplosionFrame = 0;
	explosionDuration = 70;

	toDestroy = false;
}

Missile::~Missile() {}


//setters
void Missile::setStartPosition(const exVector2& pPosition) {
	mStartPosition = pPosition;
	mPosition = pPosition;
}

void Missile::setEndPosition(const exVector2& pPosition) {
	mEndPosition = pPosition;
}

void Missile::setspeed(float speed) {

	mSpeed = speed;
}

void Missile::setType(MISSILETYPE type) {

	mType = type;
}

MISSILETYPE Missile::getType() {
	return mType;
}

//important methods
void Missile::update(float fDelta) {

	MathHelper helper;
	exVector2 distanceTraveled;
	helper.vectorRest(distanceTraveled, mPosition, mStartPosition);
	exVector2 distanceToTravel;
	helper.vectorRest(distanceToTravel, mEndPosition, mStartPosition);

	//if i havent gotten to my target
	if (helper.compareVectorsLenght(distanceTraveled, distanceToTravel)<0) {

		exVector2 movement;
		//finds the vector from start to end
		helper.vectorRest(movement, mEndPosition, mStartPosition);
		//normalize the vector to find the increment of x and y at speed 1
		helper.normilizeVector(movement, movement);
		//multiplies that vector by the speed of the missile and the delta of time
		helper.vectorScale(movement, movement, (fDelta * mSpeed));
		//adds that to the current position
		helper.vectorAdd(mPosition, mPosition, movement);

	}
	else if (currentExplosionFrame < explosionDuration) {

		//if i got to my target but the exlosion isn't over
		currentExplosionFrame++;
		collisionManagement();
	}
	else {
		//when the explosion is over i mark myself as destroyed
		toDestroy = true;
	}

}
void Missile::render() {
		//if i havent started exploding i draw a line
	if (currentExplosionFrame == 0) {

		mEngine->DrawLine(mStartPosition, mPosition, mColor, 1);
		mEngine->DrawCircle(mPosition, 2, mColor, 1);

		if (mType == MISSILETYPE::PLAYER) {

			exColor color;
			color.mColor[0] = (rand() % 255);
			color.mColor[1] = 255;
			color.mColor[2] = 255;
			color.mColor[3] = 255;

			//print horizontal cross on endPoint
			exVector2 initialPoint;
			initialPoint.x = mEndPosition.x - 5;
			initialPoint.y = mEndPosition.y;

			exVector2 endPoint;
			endPoint.x = mEndPosition.x + 5;
			endPoint.y = mEndPosition.y;

			mEngine->DrawLine(initialPoint, endPoint, color, 2);


			//print vertical line
			initialPoint.x = mEndPosition.x;
			initialPoint.y = mEndPosition.y - 5;

			endPoint.x = mEndPosition.x;
			endPoint.y = mEndPosition.y + 5;

			mEngine->DrawLine(initialPoint, endPoint, color, 2);
		}
	}
	//if i started exploding and i haven't been destroyed i blink drawing the explosion
	else if (currentExplosionFrame <= explosionDuration && !toDestroy && currentExplosionFrame%10==0){

		if (currentExplosionFrame <= explosionSize) {

			mEngine->DrawCircle(mPosition, currentExplosionFrame, mColor, 1);
		}
		else {
			mEngine->DrawCircle(mPosition, explosionSize, mColor, 1);
		}

	}

}


void Missile::collisionManagement() {

	if (mType == MISSILETYPE::ENEMY) {

		for (Target* m : DataManager::getInstance()->getTargets()) {

			if (!(m->wasHit())) {

				 MathHelper helper;

				 exVector2 distance;
				 exVector2 targetPos = m->givePosition();
				 helper.vectorRest(distance, targetPos, mPosition);

				 if (helper.giveMagnitude(distance) <= m->giveRadius() + explosionSize) {

					 m->hitTarget();
				 }
			}
		}
	}
	else if (mType == MISSILETYPE::PLAYER) {


		for (Missile* m : DataManager::getInstance()->getMissiles()) {

			if (m->getType()==MISSILETYPE::ENEMY) {

				MathHelper helper;

				exVector2 distance;
				exVector2 targetPos = m->givePosition();
				helper.vectorRest(distance, targetPos, mPosition);

				if (helper.giveMagnitude(distance) <= explosionSize) {

					m->markToDestroy();
					DataManager::getInstance()->hitEnemy();
				}
			}
		}
	}

}