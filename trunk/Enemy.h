#include "Cube.h"
#include "Player.h"
#ifndef ENEMY_H_
#define ENEMY_H_

extern GLfloat colors[][3];
class Enemy:public Cube {
public:
	Enemy(int renderModeInit, int initsize);
	virtual ~Enemy();
    Vect* raytrace(Sphere c);
private:
	int health;
	int size;
	Vertex verticesNorm[8];
};

#endif /* ENEMY_H_ */
