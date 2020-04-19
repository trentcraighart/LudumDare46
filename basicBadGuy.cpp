#include "basicBadGuy.h"
#include <random>

BasicBadGuy::BasicBadGuy() {
	frame = rand() % 4;
	timeSinceUpdate = rand() % 5000 / 10000;


	
	state = 0;
	maxState = 2;
	invul = 0;
	alive = 1;

	width = 32;
	height = 64;
	scale = 4;

	xSpeed = 200.0f;
	xDrawCoord_ = -1 * width;
	yDrawCoord = rand() % 540 + 540 - (height * scale);


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
	spriteArray = (olc::Sprite**)malloc(sizeof(olc::Sprite*) * 3);
	spriteArray[0] = new olc::Sprite("./Sprites/BadWalkRight.png");
	spriteArray[1] = new olc::Sprite("./Sprites/BadLimpRight.png");
	spriteArray[2] = new olc::Sprite("./Sprites/BadDieRight.png");

	decalArray = (olc::Decal**)malloc(sizeof(olc::Decal*) * 3);
	for (int i = 0; i < 3; i++)
		decalArray[i] = new olc::Decal(spriteArray[i]);

	//srand(time(NULL));
	int i = rand();
	if (i % 3 == 2)
		Daisy = new olc::Decal(new olc::Sprite("./Sprites/Daisy.png"));
	else if (i % 3 == 1)
		Daisy = new olc::Decal(new olc::Sprite("./Sprites/Red.png"));
	else {
		Daisy = new olc::Decal(new olc::Sprite("./Sprites/Blue.png"));
	}
}

void BasicBadGuy::updatePosition(float fEstimatedTime) {
	if (invul == 1)
		return;
	xDrawCoord_ += (fEstimatedTime * xSpeed);
	if (xDrawCoord_ > 1920)
		xDrawCoord_ = -1 * width;
}

void BasicBadGuy::drawBaddie(olc::PixelGameEngine* engine, float fEstimatedTime) {
	timeSinceUpdate += fEstimatedTime;
	if (timeSinceUpdate >= 0.15) { //frame rate for bird 
		frame++;
		if (frame > 3) //hardcoding animation length to 4
			frame = 0;
		timeSinceUpdate = 0;
	}
	if (alive == 0) {
		if (frame == 3) {
			timeSinceUpdate = 0;
			engine->DrawPartialDecal({ float(xDrawCoord_ + width * scale / 2 - 20), float(yDrawCoord + (height * scale) - 64) }, Daisy, { 0.0f, 0.0f }, { 64.0f, 64.0f }, { float(scale/4), float(scale/4) }, olc::WHITE); // THIS LINE IS CURSED A HELL
			//engine->FillRect(int(xDrawCoord_), int(yDrawCoord + height * scale / 2), int(scale * width / 2), int(scale * height / 2), olc::GREY);
			//engine->DrawString(int(xDrawCoord_), int(yDrawCoord + height * scale / 2), std::string("RIP"));
		}
		else
			engine->DrawPartialDecal({ float(xDrawCoord_), float(yDrawCoord) }, decalArray[state], { frame * 32.0f, 0.0f }, { 32.0f, 64.0f }, { float(scale), float(scale) }, olc::WHITE);

		return;
	}
	engine->DrawPartialDecal({ float(xDrawCoord_), float(yDrawCoord) }, decalArray[state], { frame * 32.0f, 0.0f }, { 32.0f, 64.0f }, { float(scale), float(scale) }, olc::WHITE);


}

bool BasicBadGuy::checkPlayerCollision(Player* player) {
	float playerx = player->xDrawCoord();
	float playery = player->yDrawCoord();
	float players = float(player->scale());
	float playerw = float(player->width());
	float playerh = float(player->height());
	//The -32 is due to bad sprite boxes, code shouldn't use this for future work
	if ((xDrawCoord_ < playerx + playerw * players + 32) && (xDrawCoord_ + float(width) * scale - 32 > playerx)) {
		if ((yDrawCoord < playery + playerh * players) && (yDrawCoord + float(height) * scale > playery))
			return true;
	}
	return false;
}
//The -32 is due to bad sprite boxes, code shouldn't use this for future work
bool BasicBadGuy::checkPlayerCollision(float playerx, float playery, float players, float playerw, float playerh) {
	if ((xDrawCoord_ < playerx + playerw * players + 64) && (xDrawCoord_ + float(width) * scale - 45 > playerx)) {
		if ((yDrawCoord < playery + playerh * players - 32) && (yDrawCoord + float(height) * scale - 32 > playery))
			return true;
	}
	return false;
}

void BasicBadGuy::step(olc::PixelGameEngine* engine, float fEstimatedTime, Player* player) {
	updatePosition(fEstimatedTime);
	drawBaddie(engine, fEstimatedTime);
	if (player->state() == 3)
		if (invul == 0 && checkPlayerCollision(player))
			takeDamage();
	if (invul == 1 && timeSinceUpdate >= 0)
		invul = 0;

}

void BasicBadGuy::step(olc::PixelGameEngine* engine, float fEstimatedTime, float playerx, float playery, float players, float playerw, float playerh, int playerState) {
	updatePosition(fEstimatedTime);
	drawBaddie(engine, fEstimatedTime);
	if (playerState == 3)
		if (invul == 0 && checkPlayerCollision(playerx, playery, players, playerw, playerh))
			takeDamage();
	if (invul == 1 && timeSinceUpdate >= 0 && alive == 1)
		invul = 0;
} 

void BasicBadGuy::takeDamage() {
	if (alive == 1) {
		timeSinceUpdate = -0.5; // invul time
		invul = 1;
		state++;
		xSpeed = xSpeed / 2;
		if (state >= maxState) {
			alive = 0;
			frame = 0;
			xSpeed = 0;
		}
	}
}
float BasicBadGuy::multiw() {
	return (scale * width);
}

float BasicBadGuy::xDrawCoord() { return xDrawCoord_; }