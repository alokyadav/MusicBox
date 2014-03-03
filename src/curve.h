#ifndef CURVE_T_H_
#define CURVE_T_H_

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <vector>

using namespace std;

class curve {

private:
	vector<float> ControlX;
	vector<float> ControlY;
	vector<float> ControlZ;

	vector<float> CurveX;
	vector<float> CurveY;
	vector<float> CurveZ;

	float sampling;

	int size;

	
	vector<float> computeCurveAtu(vector<float> pointx,vector<float> pointy,vector<float> pointz, int size, float u);
	void bezier_curve(vector<float> pointx, vector<float> pointy, vector<float> pointz);
	
public:
	curve();
	void draw();
	void drawControlPoints();
	void addControlPoint(float pointx, float pointy, float pointz);
	vector<float> getCurvePointsX();
	vector<float> getCurvePointsY();
	vector<float> getCurvePointsZ();

	void setSampling(float newsampling);

};

#endif
