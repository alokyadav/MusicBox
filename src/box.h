#ifndef BOX_T_H_
#define BOX_T_H_

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cuboid.h"



using namespace std;

class box {
	private:
		float theta ,height;
		float x, y, z;
		cuboid *cube;
		GLuint boxLid ;//= glGenLists (1);
		GLuint boxBody ;
		GLuint platform ;
		GLuint cylinder ;
		imageLoader * image_box;
		GLuint texName;

	public:
		box();
		void drawLid();
		void drawBox();
		float getTheta();
		void setTheta(float theta1);
		float getHeight();
		void setHeight(float h);
		void drawPlatform();
		void glListDef();
		void makeCheckImage(void);

};

#endif