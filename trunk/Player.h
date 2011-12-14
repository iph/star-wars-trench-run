#ifndef PLAYER_H_
#define PLAYER_H_

#pragma "Camera.h"
#pragma "Cube.h"
#include "Face.h"
class Player {
public:
	Player();
	virtual ~Player();
	bool hit(float x, float y, float z);
	bool takeDamage(int amount);
	void move(int ud, int lr);
	bool rotateRight;
	bool rotateLeft;
	bool turn;
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
