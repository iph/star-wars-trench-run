#include "Shape.h"
#include "Vect.h"
#include "Vertex.h"
#ifndef __RECTANGLE_HEADER__
#define __RECTANGLE_HEADER__

class Rectangle: public Shape{
public:
    Rectangle(int rs_i, int vs_i, int render);
    Rectangle(int rs_i, int vs_i, int render, int color);
    void makeNorms();
    void make();
    bool intersect(Vertex p, Vect d, vector <Shape *> * a);
    void changeColor(int color);
    bool intersectUnit(Vertex p, Vect d, vector <Shape *> * a);
};

#endif
