#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "player.h"
#include "basicBadGuy.h"
#include "badGuyHandler.h"

#include <iostream>
#include <string>
#include <time.h>
#include <vector>

int g_screenWidth = 1920;
int g_screenHight = 1080;
int g_screenHorizon = 540;

class Game : public olc::PixelGameEngine
{
public:
	Player* player;
	olc::Sprite* wallpaperSprite;
	olc::Decal* wallpaperDecal;
	BadGuyHandler* badGuyHandler;
	BasicBadGuy* baddie1;

	int horizon;

	Game()
	{
		sAppName = "Chicken of Legend";
	}

public:



	bool OnUserCreate() override
	{

		player = new Player(this);
		badGuyHandler = new BadGuyHandler();
		baddie1 = new BasicBadGuy();

		wallpaperSprite = new olc::Sprite();
		wallpaperSprite->LoadFromFile("./Sprites/Wallpaper1.png");
		wallpaperDecal = new olc::Decal(wallpaperSprite);
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::DARK_GREY);


		DrawDecal({0, 0}, wallpaperDecal);
		//badGuyHandler->step(this, fElapsedTime, player);

		baddie1->step(this, fElapsedTime, player);

		player->step(this, fElapsedTime);
		

		return true;
	}
};


int main()
{
	srand(time(NULL));
	Game demo;
	if (demo.Construct(g_screenWidth, g_screenHight, 1, 1, true))
		demo.Start();

	return 0;
}