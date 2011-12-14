/**************************************************************************
File: glmain.c
Does: basic lighting and modeling for cs1566 hw4 Modeler
Author: Steven Lauck, based on some hwa
Date: 01/08/09
**************************************************************************/

#include "glmain.h"
#include "Texture.h"
#include "Player.h"
#include "Face.h"
#include <stdio.h>
#define min(a,b) ((a) < (b)? a:b)
#define FALSE 0 
#define TRUE  1
#define MAX_LIGHTS  8
#define NUM_OBJECTS 8
Player player;
unsigned int rawr;
int pew = 1;
int red = 1;
int blue = 1;
int green = 1;
int diff_x = 0;
int diff_y = 0;
Scene * scene;
GLfloat vert1[3] = {-.5, -.5, 18.8};
GLfloat vert2[3] = {-.5, .5,18.8};
GLfloat vert3[3] = {.5, .5,18.8};
GLfloat vert4[3] = {.5, -.5,18.8};
//TRUE or FALSE
int firstPersonView;
void movement(int id);
void myabort(void) {
  abort();
  exit(1); /* exit so g++ knows we don't return. */
} 

int main(int argc, char** argv)
{ 
  setbuf(stdout, NULL);   /* for writing to stdout asap */
  glutInit(&argc, argv);

  my_setup(argc, argv);  
  glut_setup();
  gl_setup();

  player.setTexture();
    scene->loadTexture();
	glutMainLoop();
  return(0);
}


void glut_setup (){
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(700,700);
  glutInitWindowPosition(400,20);
  glutCreateWindow("CS1566 Project 4");

  /* set up callback functions */
  glutDisplayFunc(my_display);
  glutReshapeFunc(my_reshape);
  glutWarpPointer(350, 350);
  glutMouseFunc(my_mouse);
  glutPassiveMotionFunc(my_mouse_drag);
  glutMotionFunc(my_mouse_drag);
  glutKeyboardFunc(my_keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutIdleFunc( my_idle );	
  glutTimerFunc(200,movement, 0);
  glutIgnoreKeyRepeat(10);
  glutSetCursor(GLUT_CURSOR_NONE);

  return;
}

void gl_setup(void) {

  // enable depth handling (z-buffer)
  glEnable(GL_DEPTH_TEST);

  // enable auto normalize
  glEnable(GL_NORMALIZE);

  // define the background color 
  glClearColor(0,0,0,1);

  glMatrixMode(GL_PROJECTION) ;
  glLoadIdentity() ;
  gluPerspective( 40, 1.0, 1, 200.0);
  glMatrixMode(GL_MODELVIEW) ;
  glLoadIdentity() ;  // init modelview to identity

  // toggle to smooth shading (instead of flat)
  glShadeModel(GL_SMOOTH); 
 // lighting_setup();


  return ;
}

void my_setup(int argc, char **argv){
  firstPersonView = 1;
  //EX: ./glmain spec3
  scene = new Scene("");
  return;
}



void my_reshape(int w, int h) {
  // ensure a square view port
  glViewport(0,0,min(w,h),min(w,h)) ;
  return ;
}

void keyboardUp( unsigned char key, int x, int y ){
	 switch( key ) {
	  case ' ':
	    //code to switch between first person view and back as appropriate
	    glutPostRedisplay();
	    break;
	  case 'd':
		  player.rotateRight = false;
	    glutPostRedisplay() ;
	    break;
	  case 'a':
	    player.rotateLeft = false;
	    glutPostRedisplay() ;
	    break;

	  default: break;
	  }

	  return ;
}
void my_keyboard( unsigned char key, int x, int y ) {
  
  switch( key ) {
  case ' ':
    //code to switch between first person view and back as appropriate
    glutPostRedisplay();
    break;
  case 'd':
	  player.rotateRight = true;
    glutPostRedisplay() ;
    break;
  case 'b':
	scene->drawNorms();
	 glutPostRedisplay() ;

	break;
  case 'a':
    player.rotateLeft = true;
    glutPostRedisplay() ;
    break;
  case 'w':
    glutPostRedisplay();
    break;
  case 's':
    glutPostRedisplay();
    break;
  case 'q': 
  case 'Q':
    exit(0) ;
    break ;	
  default: break;
  }
  
  return ;
}

void my_mouse_drag(int x, int y) {
    x -= 350;
    y -= 350;
    player.changeAngle(-y,x);
    //player.move(diff_y, diff_x);
    glutWarpPointer(350, 350);
}



void my_raytrace(int mousex, int mousey)
{

	double modelViewMatrix[16];
	double projMatrix[16];
	int viewport[4];
	double clickPoint[3];

	// first we need to get the modelview matrix, the projection matrix, and the viewport
	glGetDoublev(GL_MODELVIEW_MATRIX, modelViewMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);

	// gluUnProject with a Z value of 1 will find the point on the far clipping plane
	// corresponding the the mouse click. This is not the same as the vector
	// representing the click.
	gluUnProject(mousex, (viewport[3]-mousey), 1.0, modelViewMatrix, projMatrix, viewport, &clickPoint[0], &clickPoint[1], &clickPoint[2]);

	// Now we need a vector representing the click. It should start at the camera
	// position. We can subtract the click point, we will get the vector
	Vertex far((float)clickPoint[0],(float)clickPoint[1],(float)clickPoint[2]);
	 scene->intersect(far, player.look);

}

void my_mouse(int button, int state, int mousex, int mousey) {

  switch( button ) {
	
  case GLUT_LEFT_BUTTON:
    if( state == GLUT_DOWN ) {		
		my_raytrace(mousex, mousey);
		glutPostRedisplay();

    }
    
    if( state == GLUT_UP ) {
    }
    break ;

  case GLUT_RIGHT_BUTTON:
    if ( state == GLUT_DOWN ) {		
        my_raytrace(mousex, mousey);
        glutPostRedisplay();
    }
    
    if( state == GLUT_UP ) {
    }
    break ;
  }
  

  
  return ;
}


/***********************************
 FUNCTION: draw_axes
 ARGS: none
 RETURN: none
 DOES: draws main X, Y, Z axes
************************************/




void my_display() {



  // clear all pixels, reset depth 
  glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT );
  
  glLoadIdentity();
  //setup the camera (1st person? 3rd person?)

  gluLookAt(player.look.camLocation.x,player.look.camLocation.y, player.look.camLocation.z,
	    (player.look.lookAt.x+player.look.camLocation.x), (player.look.camLocation.y+player.look.lookAt.y), (player.look.lookAt.z+player.look.camLocation.z),
	    player.look.up.x, player.look.up.y, player.look.up.z);
  //update the flashlight to follow the person
  //draw the objects
  scene->display();



  player.draw();
  glutSwapBuffers();
}

void my_idle(void) {
  //EC idea: Make the flashlight flicker a bit (random flicker strength) when the user is idle.
  return ;
}
void movement(int id){
    player.move();
   glutPostRedisplay();
   glutTimerFunc(90, movement, 0);
}
