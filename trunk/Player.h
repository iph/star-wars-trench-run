#ifndef PLAYER_H_
#define PLAYER_H_

#include "Camera.h"
#include "Cube.h"

class Player {
public:
	Player();
	virtual ~Player();
	bool hit(float x, float y, float z);
	bool takeDamage(int amount);

private:
	int health;
	Camera look;
	Cube boundingBox;
};

#endif /* PLAYER_H_ */
