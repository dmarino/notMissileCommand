//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Public/Game.h"
#include "Game/Public/Cursor.h"
#include "Game/Public/Missile.h"
#include "Game/Public/Silo.h"
#include "Game/Public/City.h"
#include "Game/Public/Target.h"
#include "Game/Public/DataManager.h"


#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include <ctime>
#include <string>
#include <windows.h>

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Not missile command";

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()

	: mEngine( nullptr )
	, mFontTittle( -1 )
	, mFontNormal(-1)
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
	DataManager::getInstance()->resetGame();
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	mEngine = pEngine;

	//initialize score manager
	DataManager::createInstance();

	//initialize random numbers
	srand(time(NULL));

	//hiding the default cursor and creating the crossed cursor
	ShowCursor(false);
	mCursor = new Cursor(pEngine);

	//initialize state
	mState = GAME_STATE::START;

	//initialize text font and thext possition
	mFontTittle = mEngine->LoadFont( "m42.ttf", 32 );
	mFontNormal = mEngine->LoadFont("Roboto.ttf", 18);

	//initialize the colors
	InitializeColors();
	createTargets();

}


//just initialize the colors
void MyGame::InitializeColors()
{

	colorWhite.mColor[0] = 255;
	colorWhite.mColor[1] = 255;
	colorWhite.mColor[2] = 255;
	colorWhite.mColor[3] = 255;

	colorBlue.mColor[0] = 0;
	colorBlue.mColor[1] = 0;
	colorBlue.mColor[2] = 255;
	colorBlue.mColor[3] = 255;

	colorRed.mColor[0] = 255;
	colorRed.mColor[1] = 0;
	colorRed.mColor[2] = 0;
	colorRed.mColor[3] = 255;

	colorYellow.mColor[0] = 255;
	colorYellow.mColor[1] = 255;
	colorYellow.mColor[2] = 0;
	colorYellow.mColor[3] = 255;

}

void  MyGame::createTargets()
{

	float distance = (kViewportHeight - 80)/6;

	exVector2 position;
	position.y = kViewportHeight -30;
	position.x = 0 +40;

	//adds first silo
	createSilo(position);

	//adds 3 cities
	for (int i = 0; i < 3; i++) {

		position.y = kViewportHeight - 20;
		position.x +=distance;

		createCity(position);
	}

	//adds middle silo
	position.x = kViewportWidth/2;
	position.y = kViewportHeight - 30;
	createSilo(position);

	//adds 3 cities more
	for (int i = 0; i < 3; i++) {

		position.y = kViewportHeight - 20;
		position.x += distance;

		createCity(position);
	}

	//adds end silo
	position.x = kViewportWidth-40;
	position.y = kViewportHeight - 30;
	createSilo(position);

}


void MyGame::createCity(exVector2 position)
{

	City* toAdd = new City(mEngine);
	toAdd->SetColor(colorBlue);
	toAdd->SetPosition(position);
	DataManager::getInstance()->addTarget(toAdd);
}

void MyGame::createSilo(exVector2 position)
{

	Silo* toAdd = new Silo(mEngine);
	toAdd->SetColor(colorBlue);
	toAdd->SetPosition(position);
	DataManager::getInstance()->addSilo(toAdd);
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 0;
	color.mColor[1] = 0;
	color.mColor[2] = 0;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent( SDL_Event* pEvent )
{
	switch (pEvent->type) {

	case SDL_MOUSEBUTTONDOWN:

		shootMissilePlayer();
		break;

	}

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

//here i manage all the players input
void MyGame::OnEventsConsumed()
{
	int nKeys = 0;
	const Uint8* pState = SDL_GetKeyboardState(&nKeys);

	if (mState == GAME_STATE::START) {

		if (pState[SDL_SCANCODE_RETURN]) { 

			mState= GAME_STATE::PLAYING; 
		}
	}
	if (mState == GAME_STATE::END) {

		if (pState[SDL_SCANCODE_RETURN]) {

			DataManager::getInstance()->resetGame();
			createTargets();
			mState = GAME_STATE::PLAYING;
		}
	}
}


void MyGame::shootMissilePlayer() {

	if (DataManager::getInstance()->getMissilesLeft() > 0)
	{

		exVector2 position = mCursor->givePosition();
		Silo* shooter = DataManager::getInstance()->getNearestSiloWithAmmo(position);

		if (shooter != nullptr)
		{
			Missile* toAdd = new Missile(mEngine);
			toAdd->SetColor(colorWhite);
			toAdd->setType(MISSILETYPE::PLAYER);
			toAdd->setspeed(90.0f);
			toAdd->setStartPosition(shooter->givePosition());
			toAdd->setEndPosition(position);
			shooter->shootMissile();
			DataManager::getInstance()->addMissile(toAdd);
		}

	}

}



void  MyGame::shootMissilesToTarget()
{

	if (DataManager::getInstance()->enemyTryShoot() == true)
	{
		Missile* toAdd = new Missile(mEngine);
		toAdd->SetColor(colorRed);
		toAdd->setspeed(40.0f);
		toAdd->setType(MISSILETYPE::ENEMY);

		Target* destination = DataManager::getInstance()->getRandomTarget();

		exVector2 origin;
		origin.x = (rand() % kViewportWidth);
		origin.y = 0;

		toAdd->setStartPosition(origin);
		toAdd->setEndPosition(destination->givePosition());
		DataManager::getInstance()->addMissile(toAdd);
	}

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------


//does different things dependding the state of the game
void MyGame::Run( float fDeltaT )
{

	//update and render the cursor
	mCursor->update(fDeltaT);
	mCursor->render();


	if (mState == GAME_STATE::START)
	{
		//just prints text

		//change the color of the text every 30 frames
		if ((mFrame % 30 ==0)) {

			textColor.mColor[0] = 100 + (rand() % 155);
			textColor.mColor[1] = 100 + (rand() % 155);
			textColor.mColor[2] = 100 + (rand() % 155);
			textColor.mColor[3] = 255;
		}

		exVector2 textPosition;
		textPosition.x = (kViewportWidth / 2) - 160.0f;
		textPosition.y = (kViewportHeight / 2) - 80.0f;
		mEngine->DrawText(mFontTittle, textPosition, "NOT", textColor, 1);

		textPosition.x = (kViewportWidth / 2) - 160.0f;
		textPosition.y = (kViewportHeight / 2) - 40.0f;
		mEngine->DrawText(mFontTittle, textPosition, "MISSILE", textColor, 1);

		textPosition.x = (kViewportWidth / 2) - 160.0f;
		textPosition.y = (kViewportHeight / 2);
		mEngine->DrawText(mFontTittle, textPosition, "COMMAND", textColor, 1);


		textPosition.x = (kViewportWidth / 2) - 80.0f;
		textPosition.y = (kViewportHeight / 2) + 80;
		mEngine->DrawText(mFontNormal, textPosition, "Press Enter to Play", colorWhite, 1);

	}
	else if(mState == GAME_STATE::PLAYING)
	{

		//draw score
		exVector2 textPosition;
		textPosition.x = 50.0f;
		textPosition.y = 50.0f;

		std::string score = std::to_string(DataManager::getInstance()->getScore());
		const char* cstr = score.c_str();
		mEngine->DrawText(mFontTittle, textPosition, cstr, textColor, 1);

		//shoot a missile every 60 frames
		if ((mFrame % 60 == 0)) {
			shootMissilesToTarget();
		}

		//render the gameObjects
		for (Target* t : DataManager::getInstance()->getTargets()) {

			if (!(t->wasHit())) {
				t->update(fDeltaT);
				t->render();
			}

		}
		for (Missile* m : DataManager::getInstance()->getMissiles()) {

			m->update(fDeltaT);
			m->render();
		}


		if (DataManager::getInstance()->checkIfEnded()) {
			mState = GAME_STATE::END;
		}

		//check if is the nextLevel
		if (DataManager::getInstance()->nextLevel())
		{
			mState = GAME_STATE::NEXTLEVEL;
			mFrameNextLevelCounter = 0;
		}
	}

	else if (mState == GAME_STATE::NEXTLEVEL)
	{	
		//just prints text again 

		mFrameNextLevelCounter++;
		if (mFrameNextLevelCounter >= 120)
		{
			mState = GAME_STATE::PLAYING;
		}

		exVector2 textPosition;
		textPosition.x = (kViewportWidth / 2);
		textPosition.y = (kViewportHeight / 2);

		std::string score = std::to_string(DataManager::getInstance()->getLevel());
		const char* cstr = score.c_str();
		mEngine->DrawText(mFontTittle, textPosition, cstr, textColor, 1);
	}

	if (mState == GAME_STATE::END)
	{
		//just prints text

		exVector2 textPosition;
		textPosition.x = (kViewportWidth / 2) - 180.0f;
		textPosition.y = (kViewportHeight / 2) - 80.0f;
		mEngine->DrawText(mFontTittle, textPosition, "GAME OVER", colorWhite, 1);

		textPosition.x = (kViewportWidth / 2) - 80.0f;
		textPosition.y = (kViewportHeight / 2) + 80;
		mEngine->DrawText(mFontNormal, textPosition, "Press Enter to Play", colorWhite, 1);

	}


	//here are the things that i do all the time
	mFrame++;
	DataManager::getInstance()->deleteDestroyedObjects();
}

