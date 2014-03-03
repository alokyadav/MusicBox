#ifndef FRUSTUM_T_H_
#define FRUSTUM_T_H_

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include "imageLoader.h"



class frustum {

private:
	float facB[3];
	float facT[3];
	float facL[3];
	float facR[3];
	float facF[3];
	float facBA[3];
	GLuint Ftexture;
public:
	frustum();
	void draw();

	void setBackfaceColor(float R,float G ,float B);
	void setBottomfaceColor(float R,float G ,float B);
	void setFrontfaceColor(float R,float G ,float B);
	void setRightfaceColor(float R,float G ,float B);
	void setLeftfaceColor(float R,float G ,float B);
	void setTopfaceColor(float R,float G ,float B);
	void setTexture(GLuint tex);

};

#endif