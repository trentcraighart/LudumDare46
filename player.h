#pragma once
#include "olcPixelGameEngine.h"



class Player
{
private:
	int frame;
	float xDrawCoord;
	float yDrawCoord;
	float yGroundCoord;

	int state; //0 idle, 1 move, 2 jump, 3 peck
	float xSpeed;
	float ySpeed;

	float yJumpSpeed;
	float jumpStart;
	
	float xspeedCap;
	float yspeedCap;
	bool left;


	float timeSinceUpdate;
	olc::Sprite** animationArray;
	olc::Decal** decalArray;



public:
	Player();

	void loadPNGAssets();
	void step(olc::PixelGameEngine *, float);
	void checkKey(olc::PixelGameEngine *, float);
	void updatePosition(float);
	void drawPlayer(olc::PixelGameEngine *, float);

};

