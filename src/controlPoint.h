#ifndef CONTROLPOINT_T_H_
#define CONTROLPOINT_T_H_

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <vector>

using namespace std;

class controlPoint {

private:
	float x, y, z;

public:
	controlPoint();
	void draw();

	void setCoordinates(float newx, float newy, float newz);
	void setZCoordinate(float newz); 
	void setYCoordinate(float newy); 
	void setXCoordinate(float newx);
	float getXCoordinate();
	float getYCoordinate();
	float getZCoordinate();

};

#endif
