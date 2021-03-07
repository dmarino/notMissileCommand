#pragma once

#include "Engine/Public/EngineTypes.h"

class exEngineInterface;

//class parent of all the objects that are going to be render
class GameObject{

public:

	GameObject(exEngineInterface* pEngine);
	~GameObject();

	//setters
	void SetPosition(const exVector2& pPosition);
	void SetColor(const exColor& pColor);
	void markToDestroy();

	//getters
	exVector2 givePosition();
	bool shouldDestroy();

	//important methods
	virtual void update(float fDelta) = 0; //this will be implemented in every child
 	virtual void render() = 0; //this will be implemented in every child

protected:

	exEngineInterface* mEngine;
	exVector2 mPosition;
	exColor mColor;

	//attributes related to lifecycle
	bool toDestroy;

};