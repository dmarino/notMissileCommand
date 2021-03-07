#pragma once

#include "Game/Public/GameObject.h"

class exEngineInterface;

//class parent of all the objects that are going to be render
class Cursor: public GameObject{

public:

	Cursor(exEngineInterface* pEngine);
	~Cursor();


	//important methods
	virtual void update(float fDelta) override; //this will be implemented in every child
 	virtual void render() override; //this will be implemented in every child

protected:

	int mSize;
};