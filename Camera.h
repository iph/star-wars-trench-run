#ifndef __CAMERA_HEADER__
#define __CAMERA_HEADER__
#include "Vect.h"
#include "Vertex.h"
#include <math.h>
class Camera{
	public:
		Camera(GLfloat *pos, GLfloat * at, GLfloat * up_i);
		void translate(float xpos, float ypos, float zpos);
		void rotate(float deg, int x, int y, int z);
    void arbitrary_rotate(float deg, GLfloat x, GLfloat y, GLfloat z);
		void updateLookAt();	
		Vect up;
		Vertex camLocation;
		Vect lookAt;
		
};


#endif
