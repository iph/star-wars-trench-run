#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include<GL/glut.h>
#endif
#include <iostream>
#include <vector>
#include "Camera.h"
#include "Shape.h"
#include "Vertex.h"
using namespace std;
#ifndef __scene_HEADER__
#define __scene_HEADER__
#define MAX_LIGHTS 8
typedef struct _LITE{
  GLfloat amb[4];
  GLfloat diff[4];
  GLfloat spec[4];
  GLfloat pos[4];
  GLfloat dir[3];
  GLfloat angle;
}LITE;
class Scene{
	friend ostream& operator<<(ostream& output, const Vect& p);
	public:
		Scene(string sceneText);	
		LITE my_lights[MAX_LIGHTS];
		vector<Shape *> shapes;
		vector<Shape *> intersects;
		Camera * cam;
		void display();
		GLfloat lighting[4][4];
		bool intersect(Vertex far);
		bool drawRay;
		void drawNorms();
	private:	
		void parseScene(string sceneText);
		void parseObject(char * buffer);
		void myabort();
		void parseFloats(char *buffer,  GLfloat nums[]);	
		void parseLight(char * buffer);
		void lightingSetup();
		void parseCamera(char * buffer);
		int num_lights;
		float x,y,z,x2,y2,z2;
};
#endif
