#include "Shape.h"
#include "Enemy.h"
#include <stdio.h>

GLfloat enemy_l[] = {0,0,20};
GLfloat enemy_at[] = {0,0,-1};
GLfloat enemy_up[] = {0,1,0};

Enemy::Enemy(int renderModeInit, int initsize)
{
	center.remake(0,0,0);
	renderMode = renderModeInit;
	size = initsize;
	rs = 1;
	vs = 8;
	verts = new Vertex *[1];
	vertsNorm = new Vertex *[1];
	for(int i = 0; i < 1; i++){
		verts[i] = new Vertex[8];
		vertsNorm[i] = new Vertex[8];
	}
	normDisplay = 0;
	make();
	makeNorm();
	health = 100;
}
Enemy::~Enemy(){
    
}

void Enemy::draw(){
	drawTriangle(verts[0], 4,5,1,GREY);
    drawTriangle(verts[0], 0,4,1,GREY);
    drawTriangle(verts[0], 5,6,2,GREY);
    drawTriangle(verts[0], 1,5,2,GREY);
    
    drawTriangle(verts[0], 0,3,7,GREY);
    drawTriangle(verts[0], 4,0,7,GREY);
    
	drawTriangle(verts[0], 4,7,5, RED);
	drawTriangle(verts[0], 5,7,6, RED); 
	if(normDisplay == 1){
        //		makeNorm();
		drawNorms();
	}
}

bool Enemy::hit(float x, float y, float z){
	// TODO: Check bounding box of ship with that of lasers/ outer objects
	return false;
}

bool Enemy::takeDamage(int amount){
	health -= amount;
	return health > 0; //Returns false when enemy dies
}

void Enemy::makeNorm(){
	//cout << "Center: " << center << endl;	
    for(int i = 0; i < 8; i++){
		//cout <<"Vert"<< i << ": " <<verts[0][i] << endl;	
		vertsNorm[0][i].remake((verts[0][i].x)*2,(verts[0][i].y)*2, (verts[0][i].z)*2);
	}
}

void Enemy::drawQuad(Vertex vertices[], int iv1, int iv2, int iv3, int iv4, int ic){
    
	GLfloat ve1[4] = {vertices[iv1].x, vertices[iv1].y, vertices[iv1].z, 1}; 
	GLfloat * ve2 = vertices[iv2].getVertex();
	GLfloat * ve3 = vertices[iv3].getVertex();
	GLfloat * ve4 = vertices[iv4].getVertex();
    
	glBegin(renderMode); 
	{
		glColor3fv(colors[ic]);
		/*note the explicit use of homogeneous coords below: glVertex4f*/
		glVertex4fv(ve1);
		glVertex4fv(ve2);
		glVertex4fv(ve3);
		glVertex4fv(ve4);
	}
	glEnd();
	delete ve2;
	delete ve3;
	delete ve4;
}
void Enemy::drawTriangle(Vertex vertices[], int iv1, int iv2, int iv3, int ic){
	GLfloat ve1[4] = {vertices[iv1].x, vertices[iv1].y, vertices[iv1].z, 1}; 
	GLfloat ve2[4] ={vertices[iv2].x, vertices[iv2].y, vertices[iv2].z, 1};
	GLfloat ve3[4] = {vertices[iv3].x, vertices[iv3].y, vertices[iv3].z, 1};
    glBegin(renderMode); 
    {
        glColor3fv(colors[ic]);
        /*note the explicit use of homogeneous coords below: glVertex4f*/
        glVertex4fv(ve1);
        glVertex4fv(ve2);
        glVertex4fv(ve3);
    }
    glEnd();
    
}

void Enemy::make() {
	GLfloat multiplier = size/2.0f;
	verts[0][0].remake(-1.0f*multiplier, size, 1.0f*multiplier); //{-1,1,1,1}
	verts[0][1].remake(1.0f*multiplier, size, 1.0f*multiplier); //{1,1,1,1}
	verts[0][2].remake(1.0f*multiplier, size, -1.0f*multiplier); //{1,1,-1,1}
	verts[0][3].remake(-1.0f*multiplier, size, -1.0f*multiplier);//{-1,1,-1,1},
    verts[0][4].remake(-1.0f*multiplier, -size, 1.0f*multiplier);//{-1,-1,1,1}, 
	verts[0][5].remake(1.0f*multiplier, -size, 1.0f*multiplier);//{1,-1,1,1}, 
	verts[0][6].remake(1.0f*multiplier, -size, -1.0f*multiplier);//{1,-1,-1,1}, 
	verts[0][7].remake(-1.0f*multiplier, -size, -1.0f*multiplier);//{-1,-1,-1,1}
}

bool Enemy::intersect(Vertex p, Vect d, vector<Shape *> * intersects){
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
bool Enemy::intersectUnit(Vertex p, Vect d, vector<Shape *> * intersects){
	float t;
	Vertex result;
	
	if(d.x != 0){
		t = (-.5f-p.x)/d.x;
		if(t >= 0){
			result.remake((p.x+d.x*t), (p.y+d.y*t), (p.z+d.z*t));
			if(result.y <= 1.0 && result.y >= -1.0 && result.z <= .5 && result.z >=-.5){
                pushIntersect(result,intersects);
            }
        }
		t = (.5f-p.x)/d.x;
		if(t >= 0){
			result.remake((p.x+d.x*t), (p.y+d.y*t), (p.z+d.z*t));
			if(result.y <= 1.0 && result.y >= -1.0 && result.z <= .5 && result.z >=-.5){
                pushIntersect(result, intersects);
            }
        }
        
        
	}
	if(d.y != 0){
		t = (-.5f-p.y)/d.y;
		if(t >= 0){
			result.remake((p.x+d.x*t), (p.y+d.y*t), (p.z+d.z*t));
			if(result.x <= .5 && result.x >= -.5 && result.z <= .5 && result.z >=-.5){
                pushIntersect(result, intersects);
            }
        }
		t = (.5f-p.y)/d.y;
		if(t >= 0){
			result.remake((p.x+d.x*t), (p.y+d.y*t), (p.z+d.z*t));
			if(result.x <= .5 && result.x >= -.5 && result.z <= .5 && result.z >=-.5){
                pushIntersect(result, intersects);
            }
        }
	}
    
	if(d.z != 0){
        t = (-.5f-p.z)/d.z;
        if(t>= 0){
            
			result.remake((p.x+d.x*t), (p.y+d.y*t), (p.z+d.z*t));
			if(result.x <= .5 && result.x >= -.5 && result.y <= 1.0 && result.y >=-1.0){
                pushIntersect(result,intersects);
            }
        }
		t = (.5f-p.z)/d.z;
		if(t >= 0){
			result.remake((p.x+d.x*t), (p.y+d.y*t), (p.z+d.z*t));
			if(result.x <= .5 && result.x >= -.5 && result.y <= 1.0 && result.y >=-1.0){
                pushIntersect(result, intersects);
            }
            
        }
	}
    
    
	return true;
}