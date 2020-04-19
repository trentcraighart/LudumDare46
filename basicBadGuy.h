#pragma once
#include "olcPixelGameEngine.h"
#include "player.h"

class BasicBadGuy
{
private:
	int frame;
	float timeSinceUpdate;

	float xDrawCoord_;
	float yDrawCoord;
	int xSpeed;

	int state;
	int maxState;
	int invul;
	int alive;

	int width;
	int height;
	int scale;

	int sprites;
	olc::Sprite** spriteArray;
	olc::Decal** decalArray;

	olc::Decal* Daisy;

public:
	BasicBadGuy();
	~BasicBadGuy();

	void loadPNGFiles();
	//step returns if they need to be destroyed
	void step(olc::PixelGameEngine*, float, Player*);
	void step(olc::PixelGameEngine*, float, float, float, float, float, float, int);
	bool checkPlayerCollision(Player*);
	bool checkPlayerCollision(float, float, float, float, float);
	void updatePosition(float);
	void drawBaddie(olc::PixelGameEngine*, float);
	void takeDamage();

	float multiw();
	float xDrawCoord();
};



