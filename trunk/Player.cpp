/*
 * Player.cpp
 */

#include "Player.h"
#include "Camera.h"
#include "Cube.h"

GLfloat l[] = {0,0,0};
GLfloat up[] = {0,0,0};
GLfloat pos[] = {0,0,0};

Player::Player()
:look(l, up, pos),
boundingBox(1, 1){

	//TODO: Figure out the camera coords of starting game.
	health = 100;
	speed = 1;
}
bool Player::hit(float x, float y, float z){
	// TODO: Check bounding box of ship with that of lasers/ outer objects
	return false;
}

bool Player::takeDamage(int amount){
	health -= amount;
	return health > 0; //Returns false when game is over
}
void Player::moveForward(){
	look.camLocation
}
Player::~Player() {
	// TODO NOTHING :D
}

