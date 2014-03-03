#ifndef CHAIR_T_H_
#define CHAIR_T_H_

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "cuboid.h"

using namespace std;

class chair {

private:
	
	GLUquadric *quad;
	cuboid *support;
	imageLoader *image_tex;
	vector<GLuint> chairParts;
	GLuint Texture;
	GLuint Texture2;
	void drawTop();
	void drawShape();
	void drawSupport();
	void drawLeg();
	void drawRod(float radius,float height);
	void drawLegSupport();
public:
	chair();
	void drawChair();	
	void init();

};

#endif