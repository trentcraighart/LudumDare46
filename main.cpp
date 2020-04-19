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
	olc::Decal* egg;
	BadGuyHandler* badGuyHandler;
	bool win, lose;
	clock_t time_start;

	int horizon;

	Game()
	{
		sAppName = "Chicken of Legend";
	}

public:



	bool OnUserCreate() override
	{
		win = false; lose = false;
		player = new Player(this);
		badGuyHandler = new BadGuyHandler();
		time_start = clock();

		wallpaperSprite = new olc::Sprite();
		wallpaperSprite->LoadFromFile("./Sprites/Wallpaper1.png");
		wallpaperDecal = new olc::Decal(wallpaperSprite);

		egg = new olc::Decal(new olc::Sprite("./Sprites/Egg.png"));
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::DARK_GREY);


		DrawDecal({0, 0}, wallpaperDecal);
		badGuyHandler->step(this, fElapsedTime, player);
		long time_left = (long)(long(time_start) - long(clock()) + 99999);
		
		if (lose != true && win != true) { //Games still going
			badGuyHandler->addBasedOnTime(time_left / 1000, fElapsedTime);
			DrawStringDecal({ float((g_screenWidth / 2) - 256), 96.0f }, std::string("WASD to move, P to peck, Space to jump\n Protect your egg!"), olc::BLACK, { 2.0f, 2.0f });
			DrawPartialDecal({ 1800.0f, 740.0f }, egg, { 0.0f, 0.0f }, { 32.0f, 32.0f }, {4.0f, 4.0f});
			if (time_left < 0) {
				win = true;
				badGuyHandler->killAll();
			}
			else
				if (badGuyHandler->checkLoss())
					lose = true;
		}
		else {
			if (win == true) {
				DrawStringDecal({ float((g_screenWidth / 2) - 256), 96.0f }, std::string("You Saved the egg!"), olc::BLACK, { 2.0f, 2.0f });
				DrawPartialDecal({ 1800.0f, 740.0f }, egg, { 64.0f, 0.0f }, { 32.0f, 32.0f }, { 4.0f, 4.0f });
			}
			else {
				badGuyHandler->addBasedOnTime(time_left / 1000, fElapsedTime);
				DrawPartialDecal({ 1800.0f, 740.0f }, egg, { 32.0f, 0.0f }, { 32.0f, 32.0f }, { 4.0f, 4.0f });
				DrawStringDecal({ float((g_screenWidth / 2) - 256), 96.0f }, std::string("The egg got smashed!"), olc::BLACK, { 2.0f, 2.0f });
			}
		}



		DrawStringDecal({ float((g_screenWidth / 2) - 128), 32.0f }, std::string("Time Left: ") + std::to_string(time_left/1000), olc::BLACK, { 2.0f, 2.0f });
		

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