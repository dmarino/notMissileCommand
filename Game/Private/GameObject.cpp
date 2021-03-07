#include "Game/Public/GameObject.h"


GameObject::GameObject(exEngineInterface* pEngine) 
	:mEngine(pEngine)
{

	//default position is 0,0
	mPosition.x = 0.0f;
	mPosition.y = 0.0f;

	//default color is white
	mColor.mColor[0] = 255;
	mColor.mColor[1] = 255;
	mColor.mColor[2] = 255;
	mColor.mColor[3] = 255;

}
GameObject::~GameObject() {

}

void GameObject::SetPosition(const exVector2& pPosition) 
{
	mPosition = pPosition;
}

void GameObject::SetColor(const exColor& pColor) 
{
	mColor = pColor;
}

void GameObject::markToDestroy()
{
	toDestroy = true;
}

exVector2 GameObject::givePosition()
{
	return mPosition;
}

bool GameObject::shouldDestroy()
{
	return toDestroy;
}