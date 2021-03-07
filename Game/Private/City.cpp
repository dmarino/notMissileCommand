#include "Game/Public/City.h"
#include "Engine/Public/EngineInterface.h"

City::City(exEngineInterface* pEngine) : Target(pEngine){}

City::~City() {}

void City::update(float fDelta) {} //cities don't move so it doesn't need to update

void City::render()
{

	float buildingSize = (mHitRadius * 2) / 5;

	exVector2 firstPoint = mPosition;
	exVector2 secondPoint = mPosition;

	//draw first building
	firstPoint.x -= mHitRadius;
	firstPoint.y += mHitRadius;
	
	secondPoint.x = firstPoint.x + buildingSize;

	mEngine->DrawBox(firstPoint, secondPoint, mColor, 1);

	//draw second building
	firstPoint.x  = secondPoint.x;

	secondPoint.x = firstPoint.x + buildingSize*2;
	secondPoint.y = mPosition.y - mHitRadius;

	mEngine->DrawBox(firstPoint, secondPoint, mColor, 1);

	//draw third building
	firstPoint.x = secondPoint.x;

	secondPoint.x = firstPoint.x + buildingSize;
	secondPoint.y = mPosition.y - (mHitRadius/2);
	mEngine->DrawBox(firstPoint, secondPoint, mColor, 1);

	exColor colorWhite;
	colorWhite.mColor[0] = 255;
	colorWhite.mColor[1] = 255;
	colorWhite.mColor[2] = 255;
	colorWhite.mColor[3] = 255;

}