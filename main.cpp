#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"



#include <iostream>
#include <string>


class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Example";
	}

public:
	olc::Sprite duck1;
	olc::Sprite duck2;
	olc::Sprite duck3;
	olc::Sprite duck4;
	int tick = 0;
	int frame = 0;
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		duck1.LoadFromFile("../Sprites/ChickenPeckLeft.png");
		duck2.LoadFromFile("../Sprites/ChickenWalkLeft.png");
		duck3.LoadFromFile("../Sprites/ChickenIdleLeft.png");
		duck4.LoadFromFile("../Sprites/ChickenFlapLeft.png");
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		tick++;
		if (tick % 200 == 0) {
			frame++;
			if (frame > 3) {
				frame = 0;
			}
		}
		DrawPartialSprite(32, 32, &duck1, (frame * 16), 0, 16, 16, 2);
		DrawPartialSprite(32*2, 32*2, &duck2, (frame * 16), 0, 16, 16, 2);
		DrawPartialSprite(32*3, 32*3, &duck3, (frame * 16), 0, 16, 16, 2);
		DrawPartialSprite(32*4, 32*4, &duck4, (frame * 16), 0, 16, 16, 2);
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
	Example demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();

	return 0;
}