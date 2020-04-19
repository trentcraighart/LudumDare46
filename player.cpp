#include "player.h"


Player::Player() {

	loadPNGAssets();

	//Setting Variables
	width_ = 16;
	height_ = 16;
	
	xSpeedCap = 200.0f;
	ySpeedCap = 120.0f;
	bLeft_ = true;
	timeSinceUpdate = 0;
	scale_ = 4;

	frame = 0;
	xDrawCoord_ = 800.0f;
	yDrawCoord_ = 580.0f;
	yGroundCoord = 580.0f;
	state_ = 0;
	xSpeed = 0;
	ySpeed = 0;
	
	yJumpSpeed = 200.0f;
	jumpStart = 0;

}

Player::Player(olc::PixelGameEngine* engine) {

	loadPNGAssets();

	//Setting Variables
	width_ = 16;
	height_ = 16;

	xSpeedCap = 200.0f;
	ySpeedCap = 120.0f;
	bLeft_ = true;
	timeSinceUpdate = 0;
	scale_ = 4;

	frame = 0;
	xDrawCoord_ = engine->ScreenWidth() / 2;
	yDrawCoord_ = 520;//engine->horizon - (scale_ * height_);
	yGroundCoord = 520;//engine->horizon - (scale_ * height_);



	state_ = 0;
	xSpeed = 0;
	ySpeed = 0;

	yJumpSpeed = 200.0f;
	jumpStart = 0;


}

void Player::loadPNGAssets() {
	spriteArray = (olc::Sprite**)malloc(sizeof(olc::Sprite*) * 8);
	spriteArray[0] = new olc::Sprite("./Sprites/ChickenIdleLeft.png");
	spriteArray[1] = new olc::Sprite("./Sprites/ChickenWalkLeft.png");
	spriteArray[2] = new olc::Sprite("./Sprites/ChickenFlapLeft.png");
	spriteArray[3] = new olc::Sprite("./Sprites/ChickenPeckLeft.png");
	spriteArray[4] = new olc::Sprite("./Sprites/ChickenIdleRight.png");
	spriteArray[5] = new olc::Sprite("./Sprites/ChickenWalkRight.png");
	spriteArray[6] = new olc::Sprite("./Sprites/ChickenFlapRight.png");
	spriteArray[7] = new olc::Sprite("./Sprites/ChickenPeckRight.png");
	decalArray = (olc::Decal**)malloc(sizeof(olc::Decal*) * 8);
	for (int i = 0; i < 8; i++)
		decalArray[i] = new olc::Decal(spriteArray[i]);
}

void Player::checkKey(olc::PixelGameEngine *engine, float fElapsedTime) {
	bool bCurLeft = engine->GetKey(olc::A).bHeld;
	bool bCurRight = engine->GetKey(olc::D).bHeld;
	if (bCurLeft == bCurRight) {
		//speed decay
		if (abs(xSpeed) < 0.4f) {
			xSpeed = 0;
		}
		else {
			xSpeed = xSpeed * 0.8 * (1.0f + fElapsedTime);
		}
	}
	else {
		if (bCurLeft) {
			xSpeed -= 1.0f;
			bLeft_ = true;
			if (xSpeed < -1 * xSpeedCap * (1.0f + fElapsedTime))
				xSpeed = -1 * xSpeedCap * (1.0f + fElapsedTime);

		}
		if (bCurRight) {
			xSpeed += 1.0f;
			bLeft_ = false;
			if (xSpeed > xSpeedCap * (1.0f + fElapsedTime))
				xSpeed = xSpeedCap * (1.0f + fElapsedTime);
		}
	}
	bool bCurUp = engine->GetKey(olc::W).bHeld;
	bool bCurDown = engine->GetKey(olc::S).bHeld;
	if (bCurUp == bCurDown) {
		//speed decay

		if (abs(ySpeed) < 0.4f) {
			ySpeed = 0;
		}
		else {
			ySpeed = ySpeed * 0.8 * (1.0f + fElapsedTime);
		}
	}
	else {
		if (bCurUp) {
			ySpeed -= 1.0f;
			//bLeft_ = true;
			if (ySpeed < -1 * ySpeedCap * (1.0f + fElapsedTime))
				ySpeed = -1 * ySpeedCap * (1.0f + fElapsedTime);
		}
		if (bCurDown) {
			ySpeed += 1.0f;
			//bLeft_ = false;
			if (ySpeed > ySpeedCap * (1.0f + fElapsedTime))
				ySpeed = ySpeedCap * (1.0f + fElapsedTime);
		}
	}
	if (engine->GetKey(olc::Key::SPACE).bPressed && (state_ < 2)) {
		state_ = 2;
		frame = 0;
		timeSinceUpdate = 0;
		jumpStart = 0;
	}
	if (engine->GetKey(olc::Key::P).bPressed && (state_ < 2)) {
		state_ = 3;
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
	if (state_ < 2) {
		if (abs(xSpeed) > 0 || abs(ySpeed) > 0)
			state_ = 1;
		else
			state_ = 0;
	}
	if (bLeft_)
		engine->DrawPartialDecal({ float(xDrawCoord_), float(yDrawCoord_) }, decalArray[state_], { frame * float(width_), 0.0f }, { float(width_), float(height_) }, { float(scale_), float(scale_) }, olc::WHITE);//, olc::Sprite::NONE);
	else
		//engine->DrawPartialDecal({ int(xDrawCoord_), int(yDrawCoord_) }, decalArray[state_], { frame * 16, 0 }, { 16, 16 }, {2, 2}, olc::Sprite::HORIZ);
		engine->DrawPartialDecal({ float(xDrawCoord_), float(yDrawCoord_) }, decalArray[state_+4], { frame * float(width_), 0.0f }, { float(width_), float(height_) }, { float(scale_), float(scale_) }, olc::WHITE);

}

void Player::updatePosition(float felapsedTime) {
	if (state_ == 3) {
		xDrawCoord_ += ((xSpeed / (frame+1)) * (felapsedTime));
		yGroundCoord += ((ySpeed / (frame+1)) * (felapsedTime));
		yDrawCoord_ = yGroundCoord;
		if (frame == 3) {
			state_ = 0;
		}
		return;
	}
	xDrawCoord_ += (xSpeed * felapsedTime);
	yGroundCoord += (ySpeed * felapsedTime);
	
	if (state_ == 2) { //Jumping
		jumpStart += felapsedTime;
		yDrawCoord_ = yGroundCoord - ((-0.5 * 300 * jumpStart * jumpStart) + (yJumpSpeed * jumpStart));
		if (yDrawCoord_ > yGroundCoord) {
			yDrawCoord_ = yGroundCoord;
			state_ = 0;
		}
	}
	else {
		yDrawCoord_ = yGroundCoord;
	}
}

void Player::checkBounds(olc::PixelGameEngine* engine) {
	float horizon = 540;
	if (yGroundCoord < horizon - (height_ * scale_) + 1)
		yGroundCoord = horizon - (height_ * scale_) + 1;
	if (yGroundCoord + (height_ * scale_) > engine->ScreenHeight())
		yGroundCoord = yGroundCoord + (height_ * scale_);
	if (xDrawCoord_ < 0)
		xDrawCoord_ = 0;
	if (xDrawCoord_ > engine->ScreenWidth() - (width_ * scale_))
		xDrawCoord_ = engine->ScreenWidth() - (width_ * scale_);
}

void Player::step(olc::PixelGameEngine *engine, float fElapsedTime) {

	checkKey(engine, fElapsedTime);
	updatePosition(fElapsedTime);
	checkBounds(engine);
	drawPlayer(engine, fElapsedTime);

}

//Getters

float Player::xDrawCoord() {
	return xDrawCoord_;
}

float Player::yDrawCoord() {
	return yDrawCoord_;
}

int Player::state() {
	return state_;
}

bool Player::bLeft() {
	return bLeft_;
}

int Player::scale() {
	return scale_;
}

int Player::width() {
	return width_;
}

int Player::height() {
	return height_;
}
