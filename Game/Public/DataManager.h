#pragma once
#include "Singleton.h"
#include <windows.h>
#include <vector>


class Missile;
class Target;
class Silo;
class exVector2;

//this is a class that stores all the info of the game in a singleton

class DataManager : public Singleton<DataManager> {

	friend class Singleton<DataManager>;

public:

	//adding methods, add stuff to the data manager lists
	void addSilo(Silo* toAdd);
	void addTarget(Target* toAdd);
	void addMissile(Missile* toAdd);

	//getters of the lists
	std::vector<Missile*> getMissiles();
	std::vector<Target*> getTargets();

	//these are for gameplay
	Target* getRandomTarget();
	Silo* getNearestSiloWithAmmo(exVector2 position);
	void restockSilos();
	void resetGame();
	void hitEnemy();

	//these are for the UI
	int getMissilesLeft();
	int getScore();
	int getLevel();

	//these are checkers
	bool nextLevel();
	bool enemyTryShoot();
	bool checkIfEnded();

	//these are for memory management
	void deleteDestroyedObjects();
	void deleteAllMissiles();
	void deleteAllTargets();
	void deleteAllSilos();

protected:

	DataManager();
	~DataManager();

	int mScore;
	int mLevel;
	int mMissilesShootInLevel;
	int mCurrentMissilesShoot;


	//vectors to store the data
	std::vector<Missile*> mMissiles;
	std::vector<Target*> mTargets;
	std::vector<Silo*> mSilos;

};

//set instance to nullptr  because is static and should have a value always, even if that value is null.
DataManager* Singleton<DataManager>::mInstance = nullptr;