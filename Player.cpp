/*
 * Player.cpp
 */

#include "Player.h"
#include "Camera.h"
#include "Cube.h"
GLfloat l[] = {0,0,20};
GLfloat at[] = {0,0,-1};
GLfloat up[] = {0,1,0};

Player::Player()
: rotateRight(false),
rotateLeft(false),
look(l, at,up),
boundingBox(1, 1)
{

	//TODO: Figure out the camera coords of starting game.
	health = 100;
//	speed = 1;
}
Player::~Player(){

}
bool Player::hit(float x, float y, float z){
	// TODO: Check bounding box of ship with that of lasers/ outer objects
	return false;
}

bool Player::takeDamage(int amount){
	health -= amount;
	return health > 0; //Returns false when game is over
}
//void Player::moveForward(){
//	look.camLocation
//}

void Player::move(){
	look.translate(0,0,-1);
	if(rotateLeft && rotateRight){}
	else if(rotateLeft){
	    look.rotate(2, 0, 0, 1);
	}
	else if(rotateRight){
	    look.rotate(-2, 0, 0, 1);
	}

}
