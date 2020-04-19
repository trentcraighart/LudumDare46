#include "badGuyHandler.h"
#include <random>
#include <time.h>
#include <stdio.h>
#include <Windows.h>
#include <cstdlib>

BadGuyHandler::BadGuyHandler() {
	timeSince = 0;
}

void BadGuyHandler::addBaddie() {
	BasicBadGuy* temp = new BasicBadGuy();
	baddies.push_back(temp);
}

void BadGuyHandler::step(olc::PixelGameEngine* engine, float fEstimatedTime, Player* player) {
	float playerx = player->xDrawCoord();
	float playery = player->yDrawCoord();
	float players = float(player->scale());
	float playerw = float(player->width());
	float playerh = float(player->height());
	int playerState = player->state();

	int i = 0, size = baddies.size();
	while (i < size) {
		BasicBadGuy* temp = baddies[i];
		temp->step(engine, fEstimatedTime, playerx, playery, players, playerw, playerh, playerState);
		i++;
	}
}

void BadGuyHandler::addBasedOnTime(long remaining, float timeElapsed) {
	timeSince += timeElapsed;
	if (timeSince > 1) {
		timeSince = 0;
		if (rand() % 100 > remaining) {
			addBaddie();
		}
	}
}

bool BadGuyHandler::checkLoss() {
	for (int i = 0; i < baddies.size(); i++) {
		if (baddies[i]->xDrawCoord() + baddies[i]->multiw() > 1800) {
			return true;
		}
	}
	return false;
}

void BadGuyHandler::killAll() {
	for (int i = 0; i < baddies.size(); i++) {
		baddies[i]->takeDamage();
		baddies[i]->takeDamage();
	}
}