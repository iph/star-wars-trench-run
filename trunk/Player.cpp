/*
 * Player.cpp
 */

#include "Player.h"

Player::Player()
:look({0,0,0},{0,0,0},{0,0,0}) {

	//TODO: Figure out the camera coords of starting game.
	health = 100;
}
bool Player::hit(float x, float y, float z){
	// TODO: Check bounding box of ship with that of lasers/ outer objects
	return false;
}
bool Player::takeDamage(int amount){
	health -= amount;
	return health > 0; //Returns false when game is over
}
Player::~Player() {
	// TODO NOTHING :D
}

