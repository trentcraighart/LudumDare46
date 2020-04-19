#pragma once
#include "olcPixelGameEngine.h"



class Player
{
private:
	int frame;
	float xDrawCoord_;
	float yDrawCoord_;
	float yGroundCoord;
	float horizon;

	int state_; //0 idle, 1 move, 2 jump, 3 peck
	float xSpeed;
	float ySpeed;

	float yJumpSpeed;
	float jumpStart;
	
	float xSpeedCap;
	float ySpeedCap;
	bool bLeft_;
	int scale_;

	float timeSinceUpdate;
	olc::Sprite** spriteArray;
	olc::Decal** decalArray;

	int width_;
	int height_;


public:
	Player();
	Player(olc::PixelGameEngine *);

	void loadPNGAssets();
	void step(olc::PixelGameEngine *, float);
	void checkKey(olc::PixelGameEngine *, float);
	void updatePosition(float);
	void drawPlayer(olc::PixelGameEngine *, float);
	
	void checkBounds(olc::PixelGameEngine *);


	float xDrawCoord();
	float yDrawCoord();
	int state();
	bool bLeft();
	int scale();
	int height();
	int width();
};

