#include "Shape.h"
#ifndef __SPHERE_HEADER__
#define __SPHERE_HEADER__

class Sphere: public Shape{
	public:
		Sphere(float r, int rs_i, int vs_i, int render);
		Sphere(float r, int rs_i, int vs_i, int render, int color);
		void makeNorms();
		void make();
		bool intersect(Vertex p, Vect d, vector <Shape *> * a);
		void changeColor(int color);
        bool intersectUnit(Vertex p, Vect d, vector <Shape *> * a);
        float radius;
};

#endif
