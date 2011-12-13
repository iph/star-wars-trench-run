#ifndef PLAYER_H_
#define PLAYER_H_

#include "Camera.h"
#include "Cube.h"
#include "Face.h"
class Player {
public:
	Player();
	virtual ~Player();
	bool hit(float x, float y, float z);
	bool takeDamage(int amount);
	void move();
	bool rotateRight;
	bool rotateLeft;
	Camera look;
	Face overlay;
	void draw();
	void setTexture();

private:
	int health;
	int speed;
	Cube boundingBox;
};

#endif /* PLAYER_H_ */
