#pragma once

#include "Game/Public/Target.h"
#include <cmath>

class exEngineInterface;

//class parent of all the objects that are going to be render
class Silo : public Target {

public:

	Silo(exEngineInterface* pEngine);
	~Silo();

	bool shootMissile();
	int giveMissilesLeft();
	float getDistanceToPoint(exVector2 pPoint);
	void restock();

	//important methods
	virtual void update(float fDelta) override;
	virtual void render() override;
	virtual void restart() override;

protected:
	int mMissilesLeft;
	int mMaxMissiles;
};