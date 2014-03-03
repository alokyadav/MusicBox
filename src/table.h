#ifndef TABLE_T_H_
#define TABLE_T_H_

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

class table {
private:
	GLUquadric *quad;
	cuboid *cube;
	frustum *hood;
	GLuint Texture;
	vector<GLuint> tableParts; 
	void createLeg();
	void drawtableTop();
	imageLoader *image_tex;

public:
	table();
	void drawTable();
	void init();
	void drawSmallTable();
};

#endif