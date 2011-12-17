#include "Camera.h"

Camera::Camera(GLfloat * pos, GLfloat * at, GLfloat * up_i): camLocation(pos[0], pos[1], pos[2]), 
lookAt(at[0],at[1],at[2]), 
up(up_i[0], up_i[1], up_i[2]){}
void Camera::translate(float xpos, float ypos, float zpos){
	camLocation.x += xpos;
	camLocation.y += ypos;
	camLocation.z += zpos;
	//cout << "Z:"<<camLocation.z  << "Lookat:"<<lookAt.z<< endl;
	//cout << camLocation.z + lookAt.z << endl;
}
void Camera::rotate(float deg, int x, int y, int z){
	Vertex temp(camLocation.x, camLocation.y, camLocation.z);
	translate((float)-camLocation.x, (float)-camLocation.y, (float)-camLocation.z);
	deg = 3.141592654f*2/180 * deg;	
	if(x == 1){
		GLfloat ypos = camLocation.y;
		GLfloat zpos = camLocation.z;
		camLocation.y = ypos*(float)cos(deg) - zpos*(float)sin(deg);
		camLocation.z = ypos*(float)sin(deg) + zpos*(float)cos(deg);
		 ypos = lookAt.y;
		 zpos = lookAt.z;
		lookAt.y = ypos*(float)cos(deg) - zpos*(float)sin(deg);
		lookAt.z = ypos*(float)sin(deg) + zpos*(float)cos(deg);

	}
	if(y == 1){
		GLfloat xpos = camLocation.x;
		GLfloat zpos = camLocation.z;
		camLocation.x = xpos*(float)cos(deg) - zpos*(float)sin(deg);
		camLocation.z = xpos*(float)sin(deg) + zpos*(float)cos(deg);
		
		 xpos = lookAt.x;
		 zpos = lookAt.z;
		lookAt.x = xpos*(float)cos(deg) - zpos*(float)sin(deg);
		lookAt.z = xpos*(float)sin(deg) + zpos*(float)cos(deg);
			
	}
	if(z == 1){
		GLfloat xpos = camLocation.x;
		GLfloat ypos = camLocation.y;
		camLocation.x = xpos*(float)cos(deg) - ypos*(float)sin(deg); 
		camLocation.y = xpos*(float)sin(deg) + ypos*(float)cos(deg);
		xpos = lookAt.x;
		ypos = lookAt.y;
		lookAt.x = xpos*(float)cos(deg) - ypos*(float)sin(deg); 
		lookAt.y = xpos*(float)sin(deg) + ypos*(float)cos(deg);
		xpos = up.x;
		ypos = up.y;
		up.x = xpos*(float)cos(deg) - ypos*(float)sin(deg);
		up.y = xpos*(float)sin(deg) + ypos*(float)cos(deg);

	}
	translate((float)temp.x, (float)temp.y, (float)temp.z);
}

void Camera::arbitrary_rotate(float deg, int x, int y, int z) {
	float tx, ty, tz, temp1, temp2, temp3, norm;
    float u[3], v[3], n[3];
	tx = camLocation.x;
	ty = camLocation.y;
	tz = camLocation.z;
    translate(-camLocation.x, -camLocation.y, -camLocation.z);
	
	if((lookAt.x == 0) && (lookAt.y == 1) && (lookAt.z == 0)) {
        rotate(deg, x, y, z);
    }
    else {
        norm = sqrt(lookAt.x*lookAt.x + lookAt.y*lookAt.y + lookAt.z*lookAt.z);
        v[0] = lookAt.x/norm;
        v[1] = lookAt.y/norm;
        v[2] = lookAt.z/norm;
        u[0] = v[2];
        u[1] = 0;
        u[2] = v[0];
        norm = sqrt(u[0]*u[0] + u[1]*u[1] + u[2]*u[2]);
        u[0] = u[0]/norm;
        u[1] = u[1]/norm;
        u[2] = u[2]/norm;
        n[0] = u[1]*v[2] - u[2]*v[1];
        n[1] = u[2]*v[0] - u[0]*v[2];
        n[2] = u[0]*v[1] - u[1]*v[0];
        norm = sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
        n[0] = n[0]/norm;
        n[1] = n[1]/norm;
        n[2] = n[2]/norm;
        
        temp1 = up.x;
        temp2 = up.y;
        temp3 = up.z;
        
        up.x = temp1*u[0] + temp2*u[1] + temp3*u[2];
        up.y = temp1*v[0] + temp2*v[1] + temp3*v[2];
        up.z = temp1*n[0] + temp2*n[1] + temp3*n[2];
        
        temp1 = lookAt.x;
        temp2 = lookAt.y;
        temp3 = lookAt.z;
            
        lookAt.x = temp1*u[0] + temp2*u[1] + temp3*u[2];
        lookAt.y = temp1*v[0] + temp2*v[1] + temp3*v[2];
        lookAt.z = temp1*n[0] + temp2*n[1] + temp3*n[2];

        rotate(deg, x, y, z, &up);
        rotate(deg, x, y, z, &lookAt);
        
        temp1 = lookAt.x;
        temp2 = lookAt.y;
        temp3 = lookAt.z;
        
        lookAt.x = temp1*u[0] + temp2*v[0] + temp3*n[0];
        lookAt.y = temp1*u[1] + temp2*v[1] + temp3*n[1];
        lookAt.z = temp1*u[2] + temp2*v[2] + temp3*n[2];
        
        temp1 = up.x;
        temp2 = up.y;
        temp3 = up.z;
        
        up.x = temp1*u[0] + temp2*v[0] + temp3*n[0];
        up.y = temp1*u[1] + temp2*v[1] + temp3*n[1];
        up.z = temp1*u[2] + temp2*v[2] + temp3*n[2];
        }
    translate(tx, ty, tz);
}
void Camera::rotate(float deg, int x, int y, int z, Vect * v){
	deg = deg*3.141592654f/180.0f;
	if(x == 1){
		GLfloat ypos = v->y;
		GLfloat zpos = v->z;
		v->y = ypos*(float)cos(deg) - zpos*(float)sin(deg);
		v->z = ypos*(float)sin(deg) + zpos*(float)cos(deg);
	}
	if(y == 1){
		GLfloat xpos = v->x;
		GLfloat zpos = v->z;
		v->x = xpos*(float)cos(deg) - zpos*(float)sin(deg);
		v->z = xpos*(float)sin(deg) + zpos*(float)cos(deg);
	}
	if(z == 1){
		GLfloat xpos = v->x;
		GLfloat ypos = v->y;
		v->x = xpos*(float)cos(deg) - ypos*(float)sin(deg); 
		v->y = xpos*(float)sin(deg) + ypos*(float)cos(deg);
	}
}

void Camera::updateLookAt(){

}
