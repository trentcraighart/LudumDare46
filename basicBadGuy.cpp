#include "basicBadGuy.h"
#include <random>

BasicBadGuy::BasicBadGuy() {
	frame = rand() % 4;
	timeSinceUpdate = rand() % 5000 / 10000;


	
	state = 0;
	maxState = 1;
	invul = 0;
	alive = 1;

	width = 32;
	height = 64;
	scale = 4;

	xSpeed = 100.0f;
	xDrawCoord = -1 * width;
	yDrawCoord = rand() % 540 + 540 - height;


	sprites = 2;
	loadPNGFiles();

}

BasicBadGuy::~BasicBadGuy() {

	for (int i = 0; i < sprites; i++) {
		decalArray[i]->~Decal();
		free(decalArray[i]);
	}
	free(decalArray);
	for (int i = 0; i < sprites; i++) {
		spriteArray[i]->~Sprite();
		free(decalArray[i]);
	}
	free(spriteArray);
}

void BasicBadGuy::loadPNGFiles() {
	spriteArray = (olc::Sprite**)malloc(sizeof(olc::Sprite*) * 2);
	spriteArray[0] = new olc::Sprite("./Sprites/BadWalkRight.png");
	spriteArray[1] = new olc::Sprite("./Sprites/BadLimpRight.png");

	decalArray = (olc::Decal**)malloc(sizeof(olc::Decal*) * 2);
	for (int i = 0; i < 2; i++)
		decalArray[i] = new olc::Decal(spriteArray[i]);
}

void BasicBadGuy::updatePosition(float fEstimatedTime) {
	if (invul == 1)
		return;
	xDrawCoord += (fEstimatedTime * xSpeed);
	if (xDrawCoord > 1920)
		xDrawCoord = -1 * width;
}

void BasicBadGuy::drawBaddie(olc::PixelGameEngine* engine, float fEstimatedTime) {
	timeSinceUpdate += fEstimatedTime;
	if (timeSinceUpdate >= 0.15) { //frame rate for bird 
		frame++;
		if (frame > 3) //hardcoding animation length to 4
			frame = 0;
		timeSinceUpdate = 0;
	}
	if (state > maxState || alive != 1) {
		return;
	}
	engine->DrawPartialDecal({ float(xDrawCoord), float(yDrawCoord) }, decalArray[state], { frame * 32.0f, 0.0f }, { 32.0f, 64.0f }, { 4.0f, 4.0f }, olc::WHITE);


}

bool BasicBadGuy::checkPlayerCollision(Player* player) {
	float playerx = player->xDrawCoord();
	float playery = player->yDrawCoord();
	float players = float(player->scale());
	float playerw = float(player->width());
	float playerh = float(player->height());

	if ((xDrawCoord < playerx + playerw * players) && (xDrawCoord + float(width) * scale > playerx)) {
		if ((yDrawCoord < playery + playerh * players) && (yDrawCoord + float(height) * scale > playery))
			return true;
	}
	return false;
}

bool BasicBadGuy::checkPlayerCollision(float playerx, float playery, float players, float playerw, float playerh) {
	if ((xDrawCoord < playerx + playerw * players) && (xDrawCoord + float(width) * scale > playerx)) {
		if ((yDrawCoord < playery + playerh * players) && (yDrawCoord + float(height) * scale > playery))
			return true;
	}
	return false;
}

void BasicBadGuy::step(olc::PixelGameEngine* engine, float fEstimatedTime, Player* player) {
	updatePosition(fEstimatedTime);
	drawBaddie(engine, fEstimatedTime);
	if (player->state() == 3)
		if (invul == 0 && checkPlayerCollision(player))
			takeDamage(engine, fEstimatedTime);
	if (invul == 1 && timeSinceUpdate >= 0)
		invul = 0;

}

void BasicBadGuy::step(olc::PixelGameEngine* engine, float fEstimatedTime, float playerx, float playery, float players, float playerw, float playerh, int playerState) {
	updatePosition(fEstimatedTime);
	drawBaddie(engine, fEstimatedTime);
	if (playerState == 3)
		if (invul == 0 && checkPlayerCollision(playerx, playery, players, playerw, playerh))
			takeDamage(engine, fEstimatedTime);
	if (invul == 1 && timeSinceUpdate >= 0)
		invul = 0;
} 

void BasicBadGuy::takeDamage(olc::PixelGameEngine* engine, float fEstimatedTime) {
	//state++;
	timeSinceUpdate = -0.5; // invul time
	invul = 1;
	state++;
	xSpeed = xSpeed / 2;
	if (state > maxState)
		alive = 0;
}