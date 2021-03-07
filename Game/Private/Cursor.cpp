#include "Game/Public/Cursor.h"
#include "Engine/Public/SDL.h"
#include "Engine/Public/EngineInterface.h"

Cursor::Cursor(exEngineInterface* pEngine) : GameObject(pEngine)
{
	mSize = 6;
}

Cursor::~Cursor() {

}

void Cursor::update(float fDelta)
{

	int x, y;
	Uint32 mouseState = SDL_GetMouseState(&x, &y);

	mPosition.x = x;
	mPosition.y = y;

}
void Cursor::render()
{


	//print horizontal line
	exVector2 initialPoint;
	initialPoint.x = mPosition.x - mSize;
	initialPoint.y = mPosition.y;

	exVector2 endPoint;
	endPoint.x = mPosition.x + mSize;
	endPoint.y = mPosition.y;

	mEngine->DrawLine(initialPoint, endPoint, mColor, 2);


	//print vertical line
	initialPoint.x = mPosition.x;
	initialPoint.y = mPosition.y- mSize;

	endPoint.x = mPosition.x;
	endPoint.y = mPosition.y + mSize;

	mEngine->DrawLine(initialPoint, endPoint, mColor, 2);
}