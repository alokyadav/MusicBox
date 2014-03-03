#ifndef FURNITURE_T_H_
#define FURNITURE_T_H_


#include "chair.h"
#include "lamp.h"
#include "table.h"

class furniture {

private:
	GLUquadric *quad;
	table* Table;
	chair* Chair;
	lamp* Lamp;
	cuboid * platForm;
	vector<GLuint> furnitureParts;
	imageLoader *image_tex;
	GLuint Texture;
	GLuint DoorTexture;
	GLuint AlmTexture;
	GLuint AlmDoorTexture;
	void createDoor();
	float doorAngle;
	void Light();
	void createAlmirah();
	void createalmirahDoor1();
	void createalmirahDoor2();
	void drawHandle();
	void createCeilLight();
public:
	
	furniture();
	void init();
	void drawPlatform();
	void drawInterior();
	void drawDoor();
	void drawRightWall();
	void drawAlmirah();


};

#endif

