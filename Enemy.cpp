#include "Enemy.h"
#include "Vertex.h"
GLfloat enemy_l[] = {0,0,20};
GLfloat enemy_at[] = {0,0,-1};
GLfloat enemy_up[] = {0,1,0};

Enemy::Enemy(int renderModeInit, int initsize): Cube(renderModeInit, initsize)
{
    remake(1, 2);
}
Enemy::~Enemy(){
    
}
Vect* Enemy::raytrace(Sphere c)     // Sphere c is the player's bounding "box"
{
    Vect * d = NULL;
    if (Vect(c.center, center).length() <= 100) {
        d = new Vect(c.center, center);
    }
    return d;
}