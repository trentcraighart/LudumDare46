#pragma once
#include <vector>
#include "olcPixelGameEngine.h"
#include "player.h"
#include "basicBadGuy.h"

class BadGuyHandler
{
private:
	std::vector<BasicBadGuy*> baddies;

	
public:
	BadGuyHandler();

	void addBaddie();
	void step(olc::PixelGameEngine*, float, Player*);
};

