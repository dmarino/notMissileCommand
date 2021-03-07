//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.h
// definition of MyGame, an implementation of exGameInterface
//

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"

#include <vector>

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class Cursor;
class Missile;
class City;
class Silo;

enum class GAME_STATE {

	START=0,
	PLAYING,
	NEXTLEVEL,
	END
};



class MyGame : public exGameInterface
{
public:

								MyGame();
	virtual						~MyGame();

	virtual void				Initialize( exEngineInterface* pEngine );

	virtual const char*			GetWindowName() const;
	virtual void				GetClearColor( exColor& color ) const;

	virtual void				OnEvent( SDL_Event* pEvent );
	virtual void				OnEventsConsumed();

	virtual void				Run( float fDeltaT );


	void                        InitializeColors();
	void                        createTargets();
	void                        createCity(exVector2 position);
	void                        createSilo(exVector2 position);

	void                        shootMissilePlayer();
	void                        shootMissilesToTarget();

private:

	exEngineInterface*			mEngine;

	int							mFontTittle;
	int							mFontNormal;

	exColor                     textColor;
	exColor                     colorWhite;
	exColor                     colorRed;
	exColor                     colorBlue;
	exColor                     colorYellow;

	GAME_STATE                  mState;
	int                         mFrame;
	int                         mFrameNextLevelCounter;

	Cursor*                     mCursor;

};
