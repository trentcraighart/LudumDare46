#include "badGuyHandler.h"
#include <random>
#include <time.h>
#include <stdio.h>
#include <Windows.h>
#include <cstdlib>

BadGuyHandler::BadGuyHandler() {

	for (int i = 0; i < 5; i++) {
		addBaddie();

	}
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
		//printf("running loop %d\n", i);
		BasicBadGuy* temp = baddies[i];
		temp->step(engine, fEstimatedTime, playerx, playery, players, playerw, playerh, playerState);

	}
}