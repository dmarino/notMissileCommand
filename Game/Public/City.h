#pragma once

#include "Game/Public/Target.h"

class exEngineInterface;

//class parent of all the objects that are going to be render
class City: public Target{

public:

	City(exEngineInterface* pEngine);
	~City();

	//important methods
	virtual void update(float fDelta) override;
 	virtual void render() override; 

};