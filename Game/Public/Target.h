#pragma once

#include "Game/Public/GameObject.h"

class exEngineInterface;

//class parent of all the objects that are going to be render
class Target: public GameObject{

public:

	Target(exEngineInterface* pEngine);
	~Target();

	//radius methods
	void setHitRadius(float radius);
	float giveRadius();


	//hitting methods
	bool wasHit();
	void hitTarget();
	virtual void restart();

protected:

	bool mHitted;

	float mHitRadius;
};