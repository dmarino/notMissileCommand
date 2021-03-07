#include "Game/Public/Silo.h"
#include "Engine/Public/EngineInterface.h"

Silo::Silo(exEngineInterface* pEngine) : Target(pEngine) {

	mMaxMissiles = 10;
	mMissilesLeft = 10;

}

Silo::~Silo() {}

void Silo::update(float fDelta) {

}

void Silo::render() {

	//draw the ceiling
	mEngine->DrawCircle(mPosition, mHitRadius,mColor, 2);

	//draw the pointy thing in the ceiling
	exVector2 firstPoint = mPosition;
	firstPoint.y -= mHitRadius;
	firstPoint.x -= 2;

	exVector2 secondPoint = mPosition;
	secondPoint.y -= mHitRadius + 10;
	secondPoint.x += 2;

	mEngine->DrawBox(firstPoint, secondPoint, mColor, 1);

	//draw the body
	firstPoint = mPosition;
	firstPoint.x -= mHitRadius;

	secondPoint = mPosition;
	secondPoint.x += mHitRadius;
	secondPoint.y += (mHitRadius+5);

	mEngine->DrawBox(firstPoint, secondPoint, mColor, 2);

	//draw the missiles left
	exColor colorWhite;
	colorWhite.mColor[0] = 255;
	colorWhite.mColor[1] = 255;
	colorWhite.mColor[2] = 255;
	colorWhite.mColor[3] = 255;

	float distance = ((mHitRadius * 2) - 10) / 5;

	for (int i = 0; i < mMissilesLeft; i++) {

		//change the row
		if (i % 5 == 0) { 
			firstPoint.x = mPosition.x - mHitRadius;
			firstPoint.y += 6;
		}

		firstPoint.x += distance;
		mEngine->DrawCircle(firstPoint, 2, colorWhite, 1);
	}
}

void Silo::restart() {

	mMissilesLeft = mMaxMissiles;
}


bool Silo::shootMissile() {
	
	if (mMissilesLeft > 0) {
		mMissilesLeft--;
		return true;
	}
	
	return false;
}

int Silo::giveMissilesLeft() {

	if (wasHit() == false)
	{
		return mMissilesLeft;
	}
	return 0;
}

float Silo::getDistanceToPoint(exVector2 pPoint) {

	float dx = pPoint.x - mPosition.x;
	float dy = pPoint.y - mPosition.y;

	float distance = sqrt(dx*dx + dy*dy);

	return distance;
}

void Silo::restock()
{
	mMissilesLeft = mMaxMissiles;
}