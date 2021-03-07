#pragma once

#include "Game/Public/GameObject.h"

class exEngineInterface;

enum class MISSILETYPE {

	PLAYER = 0,
	ENEMY
};



//class parent of all the objects that are going to be render
class Missile: public GameObject{

public:

	Missile(exEngineInterface* pEngine);
	~Missile();

	//setters
	void setStartPosition(const exVector2& pPosition);
	void setEndPosition(const exVector2& pPosition);
	void setspeed(float speed);
	void setType(MISSILETYPE type);

	//getters
	MISSILETYPE getType();

	//important methods
	virtual void update(float fDelta) override;
 	virtual void render() override; 

	//collision methods
	void collisionManagement();

protected:

	//attributes related to movement
	exVector2 mStartPosition;
	exVector2 mEndPosition;
	float mSpeed;

	//attributes related to style
	float explosionSize;
	int currentExplosionFrame;
	int explosionDuration;

	MISSILETYPE mType;
};