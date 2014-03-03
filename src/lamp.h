#ifndef LAMP_T_H_
#define LAMP_T_H_

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

class lamp {
private:
	GLUquadric *quad;
	cuboid *cube;
	frustum *hood;
	GLuint Texture;
	GLuint Skeleton_tex; 
	vector<GLuint> lampParts;
	void drawCylinder(float radiusU,float radiusL, float height);
	void drawRing(float innerR,float outerR,float thickness);
	void drawBulb();
	void drawTop(float radiusU ,float radiusL , float height ,float thickness);
	imageLoader *image_tex;
	
public:
	lamp();
	void drawSkeleton();
	void Light();
	void drawlampTable();
	void init();
	void createList();

};

#endif