#include "Rectangle.h"
#include<stdio.h>
#include<string>
#include<math.h>
Rectangle::Rectangle(int rs_i, int vs_i, int render, int color)
:Shape(rs_i,vs_i, color, "Rectangle"){
	center.remake(0,0,0);
	vertsNorm = 0;
	normDisplay = 0;
	rs = rs_i;
	vs = vs_i;
	renderMode = render;
	verts = new Vertex*[rs];
	vertsNorm = new Vertex*[rs];
	for(int i = 0; i < rs; i++){
		verts[i]=new Vertex[vs];
		vertsNorm[i]=new Vertex[vs];
	}
	make();
	makeNorms();
    
}
Rectangle::Rectangle(int rs_i, int vs_i, int render)
:Shape(rs_i,vs_i, 1, "Rectangle"){
	center.remake(0,0,0);
	vertsNorm = 0;
	normDisplay = 0;
	rs = rs_i;
	vs = vs_i;
	renderMode = render;
	verts = new Vertex*[rs];
	vertsNorm = new Vertex*[rs];
	for(int i = 0; i < rs; i++){
		verts[i]=new Vertex[vs];
		vertsNorm[i]=new Vertex[vs];
	}
	make();
	makeNorms();
}
void Rectangle::makeNorms(){
	int i = 0;
	if(normDisplay == 0){
		for(i = 0; i < rs; i++){
			delete []vertsNorm[i];
		}
        delete [] vertsNorm;
	}
	vertsNorm = new Vertex*[rs];
	for(i = 0; i < rs; i++){
		vertsNorm[i]=new Vertex[vs];
	}
	for(i = 0; i < rs; i++){
		for(int j = 0; j < vs; j++){
			vertsNorm[i][j].remake(verts[i][j].x, verts[i][j].y, verts[i][j].z+1);
			vertsNorm[i][j].normalize();
		}
	}
}
void Rectangle::make(){
    float row = -.5f;
    float col = -.5f;
	for(int i = 0; i < rs; i++)
	{
		for(int j = 0; j < vs; j++)
		{
			verts[i][j].remake(col, row, 0);
            row += 1.0f/vs;
		}
        row = -.5f;
        col += 1.0f/rs;
	}
}

bool Rectangle::intersect(Vertex p, Vect d, vector<Shape *> * intersects){
	Vertex dPoint(d.x, d.y, d.z);
	translate(-trans[0], -trans[1], -trans[2], &p);		
	rotate(-rot[2], 0, 0 , 1, &p);
	rotate(-rot[1], 0, 1 , 0, &p);
	rotate(-rot[0], 1, 0 , 0, &p);
    
	rotate(-rot[2], 0, 0 , 1, &dPoint);
	rotate(-rot[1], 0, 1 , 0, &dPoint);
	rotate(-rot[0], 1, 0 , 0, &dPoint);
	
	scale(1/scal[0], 1/scal[1], 1/scal[2], &p);
	scale(1/scal[0], 1/scal[1], 1/scal[2], &dPoint);
    
	d.x = dPoint.x;
	d.y = dPoint.y;
	d.z = dPoint.z;
    
	//Vect * newD = Vect::unitVector(d);
    
	return intersectUnit(p,d, intersects);	
}
bool Rectangle::intersectUnit(Vertex p, Vect d, vector<Shape *> * intersects){
	float t;
    Vertex result;
	if(d.z != 0){
		t = p.z/d.z;
		result.remake((p.x+d.x*t), (p.y+d.y*t), (p.z+d.z*t));
		if(result.x <= .5 && result.x >= -.5 && result.y <= .5 && result.y >=-.5){
            pushIntersect(result,intersects);
        }
    }
	return true;
}
