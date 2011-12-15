#include "Shape.h"
#include "Scene.h"
#include "Sphere.h"
#include "Vertex.h"
#include "Rectangle.h"
#include <stdlib.h>
#include "Camera.h"
#include "Cube.h"
#include "Enemy.h"
#include "Texture.h"
#include <stdio.h>
#include<string.h>
#define my_assert(X,Y) ((X)?(void) 0:(printf("error:%s in %s at %d", Y, __FILE__, __LINE__), myabort()))

	void Scene::drawNorms(){
		for(int i = 0; i < shapes.size(); i++){
			shapes[i]->changeNormDisplay((shapes[i]->getNormDisplay()+1)%2);
		}
	}


	Scene::Scene(string sceneText){
	    texture = Texture::loadTexBMP(wallTexture);

		//shapes.push_back(new Sphere(1.0,15,15, GL_POLYGON));
		num_lights = 0;
		drawRay = false;
		parseScene(sceneText);
		drawRay = 0;
	}
	ostream& operator<<(ostream& output, const Scene &p){
		output << "Scene has" ;
		return output;
	}
	void Scene::display(){
		//Sphere rawr(10.0, 15,15, GL_POLYGON);
		for (unsigned int i = 0; i < shapes.size(); i++){
		//	cout<<"SHAPE:"<< shapes[i]<< endl;
//    glMaterialfv(GL_FRONT, GL_AMBIENT, shapes[i]->amb);
 //   glMaterialfv(GL_FRONT, GL_DIFFUSE, shapes[i]->diff);
   // glMaterialfv(GL_FRONT, GL_SPECULAR, shapes[i]->spec);
   // glMaterialfv(GL_FRONT, GL_SHININESS, &shapes[i]->shine);
	glDisable(GL_LIGHTING);
			shapes[i]->draw();
		}
		for(unsigned int i = 0; i < intersects.size(); i++){
			intersects[i]->draw();
		}
		if(drawRay){
//			cout << "x" << x << endl;

		}	
	}
void Scene::parseScene(string sceneText){
    
    //char turn1[300] = "1 (0 -6 -1020 1.0) (100 30 120 1.0) (0 180 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    
    /*char enemy1[300] = "2 (-2.5 -7.75 -300 1.0) (1 2.5 2 1.0) (180 180 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char enemy2[300] = "2 (-1.7 1.05 -105 1.0) (1 2.5 2 1.0) (180 180 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char enemy3[300] = "2 (1.7 1.05 -135 1.0) (1 2.5 2 1.0) (180 180 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char enemy4[300] = "2 (1.7 1.05 -165 1.0) (1 2.5 2 1.0) (180 180 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";*/
    
        
    //char dstarl[300] = "1 (507.5 9 -550 1.0) (1000 1000 1 1.0) (-90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    //char dstarr[300] = "1 (-507.5 9 -550 1.0) (1000 1000 1 1.0) (-90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    
    char trench1lw[300] = "4 (-7.5 0 -50 1.0) (100 18 1 1.0) (0 90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench1rw[300] = "4 (7.5 0 -50 1.0) (100 18 1 1.0) (0 -90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench1bw[300] = "4 (0 -9 -50 1.0) (15 100 1 1.0) (-90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench2lw[300] = "4 (-7.5 0 -150 1.0) (100 18 1 1.0) (0 90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench2rw[300] = "4 (7.5 0 -150 1.0) (100 18 1 1.0) (0 -90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench2bw[300] = "4 (0 -9 -150 1.0) (15 100 1 1.0) (-90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench3lw[300] = "4 (-7.5 0 -250 1.0) (100 18 1 1.0) (0 90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench3rw[300] = "4 (7.5 0 -250 1.0) (100 18 1 1.0) (0 -90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench3bw[300] = "4 (0 -9 -250 1.0) (15 100 1 1.0) (-90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench4lw[300] = "4 (-7.5 0 -350 1.0) (100 18 1 1.0) (0 90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench4rw[300] = "4 (7.5 0 -350 1.0) (100 18 1 1.0) (0 -90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench4bw[300] = "4 (0 -9 -350 1.0) (15 100 1 1.0) (-90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench5lw[300] = "4 (-7.5 0 -450 1.0) (100 18 1 1.0) (0 90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench5rw[300] = "4 (7.5 0 -450 1.0) (100 18 1 1.0) (0 -90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench5bw[300] = "4 (0 -9 -450 1.0) (15 100 1 1.0) (-90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench6lw[300] = "4 (-7.5 0 -550 1.0) (100 18 1 1.0) (0 90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench6rw[300] = "4 (7.5 0 -550 1.0) (100 18 1 1.0) (0 -90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench6bw[300] = "4 (0 -9 -550 1.0) (15 100 1 1.0) (-90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench7lw[300] = "4 (-7.5 0 -650 1.0) (100 18 1 1.0) (0 90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench7rw[300] = "4 (7.5 0 -650 1.0) (100 18 1 1.0) (0 -90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench7bw[300] = "4 (0 -9 -650 1.0) (15 100 1 1.0) (-90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench8lw[300] = "4 (-7.5 0 -750 1.0) (100 18 1 1.0) (0 90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench8rw[300] = "4 (7.5 0 -750 1.0) (100 18 1 1.0) (0 -90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench8bw[300] = "4 (0 -9 -750 1.0) (15 100 1 1.0) (-90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench9lw[300] = "4 (-7.5 0 -850 1.0) (100 18 1 1.0) (0 90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench9rw[300] = "4 (7.5 0 -850 1.0) (100 18 1 1.0) (0 -90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench9bw[300] = "4 (0 -9 -850 1.0) (15 100 1 1.0) (-90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench10lw[300] = "4 (-7.5 0 -950 1.0) (100 18 1 1.0) (0 90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench10rw[300] = "4 (7.5 0 -950 1.0) (100 18 1 1.0) (0 -90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char trench10bw[300] = "4 (0 -9 -950 1.0) (15 100 1 1.0) (-90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";

    char obstacle1fw[300] = "1 (0 -5.5 -90 1.0) (15 7 1 1.0) (0 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char obstacle1tw[300] = "4 (0 -2 -140 1.0) (15 100 1 1.0) (-90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char obstacle2fw[300] = "1 (0 6.5 -254 1.0) (15 4 1 1.0) (0 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char obstacle2bw[300] = "1 (0 4.5 -256 1.0) (15 4 1 1.0) (90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char obstacle3fw[300] = "1 (5 0 -254.5 1.0) (4 18 1 1.0) (0 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char obstacle3lw[300] = "1 (3 0 -256.5 1.0) (4 18 1 1.0) (0 90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char obstacle4fw[300] = "1 (0 -7 -348 1.0) (15 4 1 1.0) (0 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char obstacle4tw[300] = "1 (0 -5 -350 1.0) (15 4 1 1.0) (90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char obstacle5fw[300] = "1 (-5 0 -348.5 1.0) (4 18 1 1.0) (0 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char obstacle5rw[300] = "1 (-3 0 -350.5 1.0) (4 18 1 1.0) (0 90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    
    char obstacle6fw[300] = "1 (0 7 -348 1.0) (15 4 1 1.0) (0 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char obstacle6bw[300] = "1 (0 5 -350 1.0) (15 4 1 1.0) (90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    
    char obstacle7fw[300] = "1 (5 0 -348.5 1.0) (4 18 1 1.0) (0 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char obstacle7lw[300] = "1 (3 0 -350.5 1.0) (4 18 1 1.0) (0 90 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    
    char obstacle8fw[300] = "1 (0 0 -348 1.0) (15 4 1 1.0) (0 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char obstacle8bw[300] = "1 (0 -2 -350 1.0) (15 4 1 1.0) (90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    char obstacle8tw[300] = "1 (0 2 -350 1.0) (15 4 1 1.0) (90 0 0 1) (0.5) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0) (1.0 1.0 1.0 1.0)";
    
    
    //parseObject(dstarl);
    //parseObject(dstarr);
    /*parseObject(enemy1);
    parseObject(enemy2);
    parseObject(enemy3);
    parseObject(enemy4);*/
    
    parseObject(trench1lw);
    parseObject(trench1rw);
    parseObject(trench1bw);
    parseObject(trench2lw);
    parseObject(trench2rw);
    parseObject(trench2bw);
    parseObject(trench3lw);
    parseObject(trench3rw);
    parseObject(trench3bw);
    parseObject(trench4lw);
    parseObject(trench4rw);
    parseObject(trench4bw);
    parseObject(trench5lw);
    parseObject(trench5rw);
    parseObject(trench5bw);
    parseObject(trench6lw);
    parseObject(trench6rw);
    parseObject(trench6bw);
    parseObject(trench7lw);
    parseObject(trench7rw);
    parseObject(trench7bw);
    parseObject(trench8lw);
    parseObject(trench8rw);
    parseObject(trench8bw);
    parseObject(trench9lw);
    parseObject(trench9rw);
    parseObject(trench9bw);
    parseObject(trench10lw);
    parseObject(trench10rw);
    parseObject(trench10bw);
    
    parseObject(obstacle1fw);
    parseObject(obstacle1tw);
    parseObject(obstacle2fw);
    parseObject(obstacle2bw);
    parseObject(obstacle3fw);
    parseObject(obstacle3lw);
    parseObject(obstacle4fw);
    parseObject(obstacle4tw);
    parseObject(obstacle5fw);
    parseObject(obstacle5rw);
    parseObject(obstacle6fw);
    parseObject(obstacle6bw);
    parseObject(obstacle7fw);
    parseObject(obstacle7lw);
    parseObject(obstacle8fw);
    parseObject(obstacle8bw);
    parseObject(obstacle8tw);

       // parseObject(buffer10);

      //  parseCamerabuffer5);
    }


void Scene::parseFloats(char *buffer, GLfloat nums[]) {
  int i;
  char *ps;

  ps = strtok(buffer, " ");
  for (i=0; ps; i++) {
    nums[i] = (float)atof(ps);
    ps = strtok(NULL, " ");
    //printf("read %f ",nums[i]);
  }

}
void Scene::lightingSetup(){
 int i;
  GLfloat globalAmb[]     = {.1f, .1f, .1f, .1f};

  // create flashlight
//  GLfloat amb[] = {0.2, 0.2, 0.2, 1.0};
//  GLfloat dif[] = {0.8, 0.8, 0.8, 1.0};
//  GLfloat spec[] = {5.0, 5.0, 5.0, 1.0};

  //enable lighting
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);

  // reflective propoerites -- global ambiant light
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

 // setup properties of lighting
  for (i=1; i<=num_lights; i++) {
    glEnable(GL_LIGHT0+i);
    glLightfv(GL_LIGHT0+i, GL_AMBIENT, my_lights[i].amb);
    glLightfv(GL_LIGHT0+i, GL_DIFFUSE, my_lights[i].diff);
    glLightfv(GL_LIGHT0+i, GL_SPECULAR, my_lights[i].spec);
    glLightfv(GL_LIGHT0+i, GL_POSITION, my_lights[i].pos);
    if ((my_lights[i].dir[0] > 0) ||  (my_lights[i].dir[1] > 0) ||  (my_lights[i].dir[2] > 0)) {
      glLightf(GL_LIGHT0+i, GL_SPOT_CUTOFF, my_lights[i].angle);
      glLightfv(GL_LIGHT0+i, GL_SPOT_DIRECTION, my_lights[i].dir);
    }
  }
}
void Scene::parseLight(char * buffer){
  LITE *pl;
  char *pamb, *pdiff, *pspec, *ppos, *pdir, *pang;
  my_assert ((num_lights < MAX_LIGHTS), "too many lights");
  pl = &my_lights[++num_lights];

  strtok(buffer, "()");
  pamb  = strtok(NULL, "()");  strtok(NULL, "()"); 
  pdiff = strtok(NULL, "()");  strtok(NULL, "()"); 
  pspec = strtok(NULL, "()");  strtok(NULL, "()"); 
  ppos  = strtok(NULL, "()");  strtok(NULL, "()"); 
  pdir  = strtok(NULL, "()");  strtok(NULL, "()"); 
  pang  = strtok(NULL, "()");

  parseFloats(pamb, pl->amb);
  parseFloats(pdiff, pl->diff);
  parseFloats(pspec, pl->spec);
  parseFloats(ppos, pl->pos);
  if (pdir) {
    parseFloats(pdir, pl->dir);
    pl->angle = (float)atof(pang);
    //printf("angle %f\n", pl->angle);
  }
  else
    pl->dir[0]= pl->dir[1]= pl->dir[2] =0;
  printf("read light\n");

}
void Scene::parseCamera(char * buffer){
  GLfloat pos[4];
	GLfloat at[4];
	GLfloat up[4];
  char *ppos, *plook, *pup;

  strtok(buffer, "()");
  ppos  = strtok(NULL, "()");  strtok(NULL, "()"); 
  plook  = strtok(NULL, "()");  strtok(NULL, "()"); 
  pup  = strtok(NULL, "()");  strtok(NULL, "()"); 

  parseFloats(ppos, pos);
  parseFloats(plook, at);
  parseFloats(pup, up);
	cam = new Camera(pos, at, up); 
}
void Scene::parseObject(char * buffer){
  Shape * curr;
  char *pshape, *pshine, *pemi, *pamb, *pdiff, *pspec, *ptranslate, *pscale, *protate;
  pshape  = strtok(buffer, " ");
   int shapeNum = atoi(pshape); 
  //printf("pshape is %s\n",pshape);
  switch (shapeNum){
      case 1: //Obstacle wall
          cout << "Obstacle Wall" << endl;
          curr = new Rectangle(1, 1, texture);
          break;
      case 2: //cube
          curr = new Enemy(GL_POLYGON, 1);
          break;
	case 3:
		curr = new Sphere(1, 2, 3, GL_POLYGON);
		break;
	case 4://Trench wall
		cout << "Trench Wall" << endl;
		curr = new Rectangle(4,4, texture);

		break;
	default:
	//	curr = new Cube(GL_POLYGON, .5);
		break;
  }
  ptranslate    = strtok(NULL, "()");  strtok(NULL, "()");
  pscale        = strtok(NULL, "()");  strtok(NULL, "()"); 
  protate       = strtok(NULL, "()");  strtok(NULL, "()");  

  pshine  = strtok(NULL, "()");strtok(NULL, "()");
  //printf("pshine is %s\n",pshine);

 
  pemi    = strtok(NULL, "()");  strtok(NULL, "()");  
  pamb    = strtok(NULL, "()");  strtok(NULL, "()"); 
  pdiff   = strtok(NULL, "()");  strtok(NULL, "()"); 
  pspec   = strtok(NULL, "()");  strtok(NULL, "()"); 
  curr->shine = (float)atof(pshine);

  parseFloats(ptranslate, curr->trans);
  parseFloats(pscale, curr->scal);
  parseFloats(protate, curr->rot);

  parseFloats(pemi, curr->emi);
  parseFloats(pamb, curr->amb);
  parseFloats(pdiff, curr->diff);
  parseFloats(pspec, curr->spec);
curr->scale(curr->scal[0], curr->scal[1], curr->scal[2]);
curr->rotate(curr->rot[0], 1, 0 , 0);
curr->rotate(curr->rot[1], 0, 1 , 0);
curr->rotate(curr->rot[2], 0, 0 , 1);
curr->translate(curr->trans[0], curr->trans[1],curr->trans[2]);
  // use switch to create your objects, cube given as example 
  printf("read object\n");
	shapes.push_back(curr);
}


void Scene::myabort(void) {
  abort();
  exit(1); /* exit so g++ knows we don't return. */
} 
bool Scene::intersect(Vertex far, Camera camer){

	bool inter = false;
	drawRay = true;
	Vertex p = camer.camLocation;
	x = far.x;
	y = far.y;
	z = far.z;
	x2 = camer.camLocation.x;
	y2 = camer.camLocation.y;
	z2 = camer.camLocation.z;
	Vect * d = Vect::unitVector(*(new Vect(p, far)));
	for(int i = 0; i < shapes.size(); i++){
		if(shapes[i]->intersect(p,*d, &intersects)){
			inter = true;
			cout << "HIT OBJECT " << i << endl;
            break;
		}
	}
	return inter;
}

void Scene::loadTexture() {

    texture = Texture::loadTexBMP(wallTexture);
    for(int j = 0; j < shapes.size(); j++){
		shapes[j]->setTexture(texture);
    }

}

