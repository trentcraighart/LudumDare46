#include "player.h"


Player::Player() {
	animationArray = (olc::Sprite**)malloc(sizeof (olc::Sprite*) * 4);
	animationArray[0] = new olc::Sprite("./Sprites/ChickenIdleLeft.png");
	animationArray[1] = new olc::Sprite("./Sprites/ChickenWalkLeft.png");
	animationArray[2] = new olc::Sprite("./Sprites/ChickenFlapLeft.png");
	animationArray[3] = new olc::Sprite("./Sprites/ChickenPeckLeft.png");

	frame = 0;
	xDrawCoord = 32.0f;
	yDrawCoord = 32.0f;
	yGroundCoord = 32.0f;

	state = 0;
	xSpeed = 0;
	ySpeed = 0;
	
	yJumpSpeed = 200.0f;
	jumpStart = 0;

	xspeedCap = 200.0f;
	yspeedCap = 120.0f;
	left = true;
	timeSinceUpdate = 0;
}

void Player::checkKey(olc::PixelGameEngine *engine, float fElapsedTime) {
	bool curLeft = engine->GetKey(olc::A).bHeld;
	bool curRight = engine->GetKey(olc::D).bHeld;
	if (curLeft == curRight) {
		//speed decay
		if (abs(xSpeed) < 0.4f) {
			xSpeed = 0;
		}
		else {
			xSpeed = xSpeed * 0.8 * (1.0f + fElapsedTime);
		}
	}
	else {
		if (curLeft) {
			xSpeed -= 1.0f;
			left = true;
			if (xSpeed < -1 * xspeedCap * (1.0f + fElapsedTime))
				xSpeed = -1 * xspeedCap * (1.0f + fElapsedTime);

		}
		if (curRight) {
			xSpeed += 1.0f;
			left = false;
			if (xSpeed > xspeedCap * (1.0f + fElapsedTime))
				xSpeed = xspeedCap * (1.0f + fElapsedTime);
		}
	}
	bool curUp = engine->GetKey(olc::W).bHeld;
	bool curDown = engine->GetKey(olc::S).bHeld;
	if (curUp == curDown) {
		//speed decay

		if (abs(ySpeed) < 0.4f) {
			ySpeed = 0;
		}
		else {
			ySpeed = ySpeed * 0.8 * (1.0f + fElapsedTime);
		}
	}
	else {
		if (curUp) {
			ySpeed -= 1.0f;
			left = true;
			if (ySpeed < -1 * yspeedCap * (1.0f + fElapsedTime))
				ySpeed = -1 * yspeedCap * (1.0f + fElapsedTime);
		}
		if (curDown) {
			ySpeed += 1.0f;
			left = false;
			if (ySpeed > yspeedCap * (1.0f + fElapsedTime))
				ySpeed = yspeedCap * (1.0f + fElapsedTime);
		}
	}
	if (engine->GetKey(olc::Key::SPACE).bPressed && (state < 2)) {
		state = 2;
		frame = 0;
		timeSinceUpdate = 0;
		jumpStart = 0;
	}
	if (engine->GetKey(olc::Key::P).bPressed && (state < 2)) {
		state = 3;
		frame = 0;
		timeSinceUpdate = 0;
		jumpStart = 0;
	}
}

void Player::drawPlayer(olc::PixelGameEngine *engine, float felapsedTime) {
	//Moderate the bird's framerate
	timeSinceUpdate += felapsedTime;
	if (timeSinceUpdate >= 0.15) { //frame rate for bird 
		frame++;
		if (frame > 3) //hardcoding animation length to 4
			frame = 0;
		timeSinceUpdate = 0;
	}
	if (state < 2) {
		if (abs(xSpeed) > 0 || abs(ySpeed) > 0)
			state = 1;
		else
			state = 0;
	}
	if (left)
		engine->DrawPartialSprite({ int(xDrawCoord), int(yDrawCoord) }, animationArray[state], { frame * 16, 0 }, { 16, 16 }, 2, olc::Sprite::NONE);
	else
		engine->DrawPartialSprite({ int(xDrawCoord), int(yDrawCoord) }, animationArray[state], { frame * 16, 0 }, { 16, 16 }, 2, olc::Sprite::HORIZ);
		

}

void Player::updatePosition(float felapsedTime) {
	if (state == 3) {
		xDrawCoord += ((xSpeed / (frame+1)) * (felapsedTime));
		yGroundCoord += ((ySpeed / (frame+1)) * (felapsedTime));
		yDrawCoord = yGroundCoord;
		if (frame == 3) {
			state = 0;
		}
		return;
	}
	xDrawCoord += (xSpeed * felapsedTime);
	yGroundCoord += (ySpeed * felapsedTime);
	
	if (state == 2) { //Jumping
		jumpStart += felapsedTime;
		yDrawCoord = yGroundCoord - ((-0.5 * 300 * jumpStart * jumpStart) + (yJumpSpeed * jumpStart));
		if (yDrawCoord > yGroundCoord) {
			yDrawCoord = yGroundCoord;
			state = 0;
		}
	}
	else {
		yDrawCoord = yGroundCoord;
	}


}


void Player::step(olc::PixelGameEngine *engine, float fElapsedTime) {

	checkKey(engine, fElapsedTime);
	updatePosition(fElapsedTime);
	drawPlayer(engine, fElapsedTime);

}