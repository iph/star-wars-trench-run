#include "Shape.h"
#ifndef ENEMY_H_
#define ENEMY_H_

extern GLfloat colors[][3];
class Enemy:public Shape {
public:
	Enemy(int renderModeInit, int initsize);
	virtual ~Enemy();
	bool hit(float x, float y, float z);
	bool takeDamage(int amount);
	void draw();
	void make();
	void makeNorm();
	void drawQuad(Vertex vertices[], int iv1, int iv2, int iv3, int iv4, int ic);
	void drawTriangle(Vertex vertices[], int iv1, int iv2, int iv3, int ic);
	bool intersect(Vertex p, Vect d, vector <Shape *> * a);
	bool intersectUnit(Vertex p, Vect d, vector <Shape *> * a);
private:
	int health;
	int size;
	Vertex verticesNorm[8];
};

#endif /* ENEMY_H_ */
