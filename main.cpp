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
	Game()
	{
		player = NULL;
		sAppName = "Chicken of Legend";
	}

public:



	bool OnUserCreate() override
	{

		player = new Player();
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::DARK_GREY);
		player->step(this, fElapsedTime);

		//DrawPartialSprite(32, 32, &duck1, (frame % 4 * 16), 0, 16, 16, 4);
		//DrawPartialSprite(32*2, 32*2, &duck2, (frame * 16), 0, 16, 16, 2);
		//DrawPartialSprite(32*3, 32*3, &duck3, (frame * 16), 0, 16, 16, 2);
		//DrawPartialSprite(32*4, 32*4, &duck4, (frame * 16), 0, 16, 16, 2);
		// called once per frame
		/*for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand() % 255));
		*/
		return true;
	}
};


int main()
{
	Game demo;
	if (demo.Construct(500, 500, 4, 4))
		demo.Start();

	return 0;
}