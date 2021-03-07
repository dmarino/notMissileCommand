#include "Game/Public/DataManager.h"
#include "Game/Public/Missile.h"
#include "Game/Public/Silo.h"


DataManager::DataManager()
{

	mScore = 0;
	mLevel = 1;
	mMissilesShootInLevel = 15;
	mCurrentMissilesShoot = 0;
}


DataManager::~DataManager() 
{

	deleteAllMissiles();
	deleteAllTargets();
	deleteAllSilos();
}


void DataManager::addSilo(Silo* toAdd)
{

	mSilos.push_back(toAdd);
	mTargets.push_back(toAdd);
}


void DataManager::addTarget(Target* toAdd)
{

	mTargets.push_back(toAdd);
}


void DataManager::addMissile(Missile* toAdd)
{

	mMissiles.push_back(toAdd);
}

std::vector<Missile*> DataManager::getMissiles()
{
	return mMissiles;
}

std::vector<Target*> DataManager::getTargets() 
{
	return mTargets;
}

Target* DataManager::getRandomTarget() 
{

	while (!checkIfEnded())
	{

		int pos = (rand() % mTargets.size());
		Target* toReturn = mTargets.at(pos);

		if (!(toReturn->wasHit()))
		{
			return toReturn;
		}
	}

}

void DataManager::deleteDestroyedObjects() 
{

	std::vector<Missile*> missilesToDelete;

	for (Missile* m : mMissiles)
	{
		if (m->shouldDestroy())
		{
			missilesToDelete.push_back(m);
		}
	}

	for (Missile* m : missilesToDelete)
	{
		delete m;
		mMissiles.erase(std::remove(mMissiles.begin(), mMissiles.end(),m),mMissiles.end());
	}
}

int DataManager::getMissilesLeft() 
{

	int missiles = 0;
	for (Silo* s : mSilos)
	{
		missiles += s->giveMissilesLeft();
	}

	return missiles;
}

Silo* DataManager::getNearestSiloWithAmmo(exVector2 position) 
{

	//this is a number bigger than any screen so it will never be smaller than any
	//actual distance
	float minDistance = 10000000;
	Silo* siloToReturn = nullptr;

	for (Silo* s : mSilos)
	{
		if (s->wasHit() == false && s->giveMissilesLeft()>0)
		{
			float tempDistance = s->getDistanceToPoint(position);
			if ( tempDistance < minDistance)
			{
				minDistance = tempDistance;
				siloToReturn = s;
			}
		}
	}

	return siloToReturn;
}

bool DataManager::checkIfEnded()
{

	for (Target* t : mTargets)
	{

		if (t->wasHit()==false) {

			return false;
		}
	}

	return true;
}

bool DataManager::enemyTryShoot()
{

	if (mCurrentMissilesShoot < mMissilesShootInLevel) 
	{
		mCurrentMissilesShoot++;
		return true;
	}

	return false;
}

bool DataManager::nextLevel() 
{

	if (mCurrentMissilesShoot == mMissilesShootInLevel)
	{
		for (Missile* m : mMissiles)
		{
			if (m->getType() == MISSILETYPE::ENEMY)
			{
				return false;
			}
		}

		mMissiles.clear();
		mMissiles.shrink_to_fit();

		restockSilos();

		mLevel++;
		mCurrentMissilesShoot = 0;
		mMissilesShootInLevel = mMissilesShootInLevel * mLevel;
		return true;
	}

	return false;
}

void DataManager::restockSilos() 
{

	for (Silo* s : mSilos)
	{
		if (s->wasHit() == false)
		{
			s->restock();
		}
	}
}

void DataManager::resetGame()
{

	deleteAllMissiles();
	deleteAllTargets();
	deleteAllSilos();


	mLevel = 1;
	mMissilesShootInLevel = 15;
	mCurrentMissilesShoot = 0;
	mScore = 0;

}

void DataManager::hitEnemy()
{

	mScore += 25;
}

int DataManager::getScore() 
{

	return mScore;
}

int DataManager::getLevel() 
{

	return mLevel;
}

void DataManager::deleteAllMissiles()
{
	for (Missile* m : mMissiles)
	{
		delete m;
	}
	mMissiles.clear();
}

void DataManager::deleteAllTargets()
{
	for (Target* t : mTargets)
	{
		delete t;
	}
	mTargets.clear();
}

void DataManager::deleteAllSilos()
{
	//i don't delete the silos cause they get deleted in the targets
	mSilos.clear();
}