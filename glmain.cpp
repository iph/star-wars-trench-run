/**************************************************************************
File: glmain.c
Does: basic lighting and modeling for cs1566 hw4 Modeler
Author: Steven Lauck, based on some hwa
Date: 01/08/09
**************************************************************************/

#include "glmain.h"
#include "Texture.h"
#include "Player.h"
#define min(a,b) ((a) < (b)? a:b)
#define FALSE 0 
#define TRUE  1
#define MAX_LIGHTS  8
#define NUM_OBJECTS 8
Player a;
Scene * scene;
GLfloat vert1[3] = {-.5, -.5, 19};
GLfloat vert2[3] = {-.5, .5,19};
GLfloat vert3[3] = {.5, .5,19};
GLfloat vert4[3] = {.5, -.5,19};
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

  glutMainLoop();
  return(0);
}


void glut_setup (){

  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  
  glutInitWindowSize(700,700);
  glutInitWindowPosition(20,20);
  glutCreateWindow("CS1566 Project 4");

  /* set up callback functions */
  glutDisplayFunc(my_display);
  glutReshapeFunc(my_reshape);
  glutMouseFunc(my_mouse);
  glutMotionFunc(my_mouse_drag);
  glutKeyboardFunc(my_keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutIdleFunc( my_idle );	
  glutTimerFunc( 200,movement, 0);
  glutIgnoreKeyRepeat(10);
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
		  a.rotateRight = false;
	    glutPostRedisplay() ;
	    break;
	  case 'a':
	    a.rotateLeft = false;
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
	  a.rotateRight = true;
    glutPostRedisplay() ;
    break;
  case 'b':
	scene->drawNorms();
	 glutPostRedisplay() ;

	break;
  case 'a':
    a.rotateLeft = true;
    glutPostRedisplay() ;
    break;
  case 'w':
    //scene->cam->translate(0,0,-1);

    glutPostRedisplay();
    break;
  case 's':
   //scene->cam->translate(0,0,1);
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
	 scene->intersect(far, a.look);

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

  gluLookAt(a.look.camLocation.x,a.look.camLocation.y, a.look.camLocation.z,
	    (a.look.lookAt.x+a.look.camLocation.x), (a.look.camLocation.y+a.look.lookAt.y), (a.look.lookAt.z+a.look.camLocation.z),
	    a.look.up.x, a.look.up.y, a.look.up.z);
  //update the flashlight to follow the person
  //draw the objects
  scene->display();

  unsigned int rawr = Texture::loadTexBMP("images/xwing.bmp");
  glEnable(GL_TEXTURE_2D);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /* using the current texture */
    glBindTexture(GL_TEXTURE_2D,rawr);

    /* Cube */
    glBegin(GL_QUADS);
    /* front => ABCD yellow */
    glNormal3f(0,0,1);
   // glColor4f(1.0, 1.0, 1.0, 0.0);
    glTexCoord2f(0,0); glVertex3fv(vert2);
    glTexCoord2f(1,0); glVertex3fv(vert3);
    glTexCoord2f(1,1); glVertex3fv(vert4);
    glTexCoord2f(0,1); glVertex3fv(vert1);
    glEnd();
  glDisable(GL_TEXTURE_2D);
  glutSwapBuffers();
}

void my_idle(void) {
  //EC idea: Make the flashlight flicker a bit (random flicker strength) when the user is idle.
  return ;
}
void movement(int id){
   a.move();
   vert1[2] -= 1;
   vert2[2] -= 1;
   vert3[2] -= 1;
   vert4[2] -= 1;
   glutPostRedisplay();
   glutTimerFunc(90, movement, 0);
}
