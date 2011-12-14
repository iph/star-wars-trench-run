/*
 * Player.cpp
 */

#include "Player.h"
#include "Texture.h"
GLfloat player_l[] = {0,0,20};
GLfloat player_at[] = {0,0,-1};
GLfloat player_up[] = {0,1,0};

Player::Player()
: rotateRight(false),
rotateLeft(false),
turn(false),
look(player_l, player_at,player_up),
boundingBox(1, 1)
{
	  overlay.bottomRight.remake(-.5, .5, 18.8);
	  overlay.bottomLeft.remake(-.5, -.5, 18.8);
	  overlay.topRight.remake(.5, .5, 18.8);
	  overlay.topLeft.remake(.5, -.5, 18.8);

	//TODO: Figure out the camera coords of starting game.
	health = 100;
//	speed = 1;
}
Player::~Player(){

}
void Player::setTexture(){
	  unsigned int rawr = Texture::loadTexBMP("xwing.bmp");
	  overlay.setTexture(rawr);
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

void Player::move(int ud, int lr){
    Vertex loc = look.camLocation;
    double norm = look.lookAt.x + look.lookAt.y + look.lookAt.z;
	look.translate(-look.lookAt.x/norm,-look.lookAt.y/norm,look.lookAt.z/norm);
	overlay.translate(-look.lookAt.x/norm,-look.lookAt.y/norm,look.lookAt.z/norm);
	if(rotateLeft && rotateRight){}
	else if(rotateLeft){
	    look.rotate(2, 0, 0, 1);
	    overlay.rotate(2,0,0,1);
	}
	else if(rotateRight){
	    look.rotate(-2, 0, 0, 1);
	    overlay.rotate(-2,0,0,1);
	}
    if(turn) {
        look.rotate(lr, 1, 0, 0);
        overlay.rotate(lr, 1, 0, 0, &loc);
        look.rotate(ud, 0, 1, 0);
        overlay.rotate(ud, 0, 1, 0, &loc);
    }
}
void Player::draw(){
	overlay.draw();
}
