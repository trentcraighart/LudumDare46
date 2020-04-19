#pragma once
#include <vector>
#include "olcPixelGameEngine.h"
#include "player.h"
#include "basicBadGuy.h"

class BadGuyHandler
{
private:
	std::vector<BasicBadGuy*> baddies;
	float timeSince;
	
public:
	BadGuyHandler();

	void addBaddie();
	void step(olc::PixelGameEngine*, float, Player*);
	bool checkLoss();
	void killAll();
	void addBasedOnTime(long, float);
};

