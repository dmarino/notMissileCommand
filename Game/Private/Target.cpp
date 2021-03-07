#include "Game/Public/Target.h"
#include "Game/Public/MathHelper.h"
#include "Engine/Public/EngineInterface.h"

Target::Target(exEngineInterface* pEngine) : GameObject(pEngine)
{
	mHitted = false;
	mHitRadius = 20.0f;
}

Target::~Target() {

}

void Target::setHitRadius(float radius) {
	mHitRadius = radius;
}

float Target::giveRadius() {
	return mHitRadius;
}

bool Target::wasHit() {
	return mHitted;
}
void Target::hitTarget() {
	mHitted = true;
}
void Target::restart() {

	mHitted = false;
}