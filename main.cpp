#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "player.h"


#include <iostream>
#include <string>
#include <time.h>


class Game : public olc::PixelGameEngine
{
public:
	Player* player;
	olc::Sprite* wallpaperSprite;
	olc::Decal* wallpaperDecal;
	Game()
	{
		player = NULL;
		wallpaperSprite = NULL;
		sAppName = "Chicken of Legend";
	}

public:



	bool OnUserCreate() override
	{

		player = new Player();
		wallpaperSprite = new olc::Sprite();
		wallpaperSprite->LoadFromFile("./Sprites/Wallpaper1.png");
		wallpaperDecal = new olc::Decal(wallpaperSprite);
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		//Clear(olc::DARK_GREY);


		DrawDecal({0, 0}, wallpaperDecal);
		player->step(this, fElapsedTime);

		return true;
	}
};


int main()
{
	Game demo;
	if (demo.Construct(1920, 1080, 1, 1, false))
		demo.Start();

	return 0;
}