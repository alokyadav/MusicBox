#include "box.h"
#include "cuboid.h"
#include "frustum.h"
#include "human.h"
#include "furniture.h"
#include "curve.h"
#include "controlPoint.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>


using namespace std;

//Window dimensions
int win_width = 1024;
int win_height = 768;

//Record mode
bool recordMode = false;

//Light variables
bool light1=1;
bool light0=1;

//Eye coordinates
float angle = -(M_PI)/2;
float radius = 20.0;

//Used to model the opening of the box
float modelHeight = -1.0f;

//Bezier curve sampling. 0 < sampling < 1
float sampling = 0.01f;

//Used for the bezier curve interfacing
bool bezierMode = false;
bool controlPointFlag = false;
bool addControlPointFlag = false;

//used for the timer
int timerIndex = 0;

int animationStep = 0;

//Camera coordinates
vector<float> camera(3);

//Path used for moving camera on bezier curve
vector<float> cameraPathX;
vector<float> cameraPathY;
vector<float> cameraPathZ;

//Frames for animation
vector<vector<float> > frames;

//initialize various objects
box *outerBox = new box();
human *model = new human();
cuboid *cube = new cuboid();
furniture * roomInterior = new furniture();
curve * bezier = new curve();
controlPoint * currentControlPoint;


void init(){
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	roomInterior->init();
    model->init();
    outerBox->glListDef();

}

void modifyLookAt(vector<float> camera1){
	glLoadIdentity();
	gluLookAt(camera1[0], camera1[1], camera1[2], 0.0f, 0.0f, 0.0f, camera1[0], camera1[1] + 1.0f, camera1[2]);
	glutPostRedisplay();
}

void display( void )
{
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    

    if(light0){
		glEnable(GL_LIGHT0);
	}
    if(light1){
		glEnable(GL_LIGHT1);
	}

    // Draw Room
   	glPushMatrix();
	   	glTranslatef(0.0f, -5.0f, 0.0f);
	   	roomInterior->drawInterior();
	   	if(!bezierMode){
	   		roomInterior->drawRightWall();
	   	}
  	glPopMatrix();

  	//Draw Model
  	glPushMatrix();
  		glTranslatef(0.0f, modelHeight, 0.0f);
  		glScalef(0.2f, 0.2f, 0.2f);
  		model->draw();
  	glPopMatrix();

  	//Draw Box
  	glPushMatrix();
  		glTranslatef(0.0f, -1.6f, 0.0f);
  		outerBox->drawBox();
  	glPopMatrix();

  	//Draw Bezier Curve
  	bezier->draw();
  	if(controlPointFlag){
  		currentControlPoint->draw();
  	}



    glutSwapBuffers(); //Send the 3D scene to the screen
}

void initControlPoint(int x, int y){
	currentControlPoint = new controlPoint();
	controlPointFlag = true;
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLdouble posX, posY, posZ;
	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport);
	gluUnProject( x, y, 0.95, modelview, projection, viewport, &posX, &posY, &posZ);
	currentControlPoint->setCoordinates(posX, -posY, posZ);
	radius = 30.0f;
	angle = 0.0f;
	camera[0] = radius*cos(angle);
  	camera[1] = 0.0;
  	camera[2] = -radius*sin(angle);
  	modifyLookAt(camera);
}

void mouse(int button, int state, int x, int y) 
{
	if(addControlPointFlag){
		addControlPointFlag = false;
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			initControlPoint(x, y);			
		}
	}
    glutPostRedisplay();
}

void moveCameraOnCurve(int extra){
	if(timerIndex < cameraPathX.size()){
		camera[0] = cameraPathX[timerIndex];
		camera[1] = cameraPathY[timerIndex];
		camera[2] = cameraPathZ[timerIndex];
		timerIndex++;
		glutTimerFunc(50,moveCameraOnCurve,0);
		modifyLookAt(camera);
	}
	else{
		radius = 1.0f;
		angle = (-M_PI)/2;
		camera[0] = radius*cos(angle);
		camera[1] = 0.0;
		camera[2] = -radius*sin(angle);
		modifyLookAt(camera);
	}
	
}

void setCameraPath(){

	cameraPathX = bezier->getCurvePointsX();
	cameraPathY = bezier->getCurvePointsY();
	cameraPathZ = bezier->getCurvePointsZ();
	glutTimerFunc(0,moveCameraOnCurve,0);
}

void reshape( int w, int h )
{
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION); 
    
    //Set the camera perspective
    glLoadIdentity(); 
    gluPerspective(45.0,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   1000.0);               //The far z clipping coordinate
    glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();
  	gluLookAt(radius*cos(angle), 0.0, -radius*sin(angle), 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
}

ofstream keyFrame_capture;
void Record(){
	keyFrame_capture.open ("keyframes.txt",ios::app );
	keyFrame_capture << light0 << " " << light1 << " ";
	keyFrame_capture << outerBox->getTheta()<<" "<<outerBox->getHeight()<<" ";
	keyFrame_capture << model->hipAngleX <<" "<<model->hipAngleY<<" "<<model->hipAngleZ<<" ";
	keyFrame_capture << model->stomachAngleX <<" "<<model->stomachAngleY <<" "<<model->stomachAngleZ<<" ";
	keyFrame_capture << model->neckAngleX <<" "<< model->neckAngleY <<" "<<model->neckAngleZ<<" ";
	keyFrame_capture << model->headAngleX  <<" "<< model->headAngleY <<" "<<model->headAngleZ<<" ";
	keyFrame_capture << model->chestAngleX <<" "<<model->chestAngleY <<" "<<model->chestAngleZ<< " ";
	keyFrame_capture << model->armAngleLeftX <<" "<<model->armAngleLeftY<<" "<< model->armAngleLeftZ<< " ";
	keyFrame_capture << model->armAngleRightX <<" "<<model->armAngleRightY<<" "<<model->armAngleRightZ<<" ";
	keyFrame_capture << model->elbowAngleLeft <<" "<<model->elbowAngleRight<<" ";
	keyFrame_capture << model->legAngleLeftX <<" "<<model->legAngleLeftY<<" "<<model->legAngleLeftZ<<" ";
	keyFrame_capture << model->legAngleRightX << " "<<model->legAngleRightY<<" "<<model->legAngleRightZ<<" ";
	keyFrame_capture << model->kneeAngleLeft <<" "<<model->kneeAngleRight<<endl;
	keyFrame_capture.close(); 
}

void interpolate(vector<float> &initialKeyframe, vector<float> &finalKeyframe, vector<float> &result, int i){
	if(i == 10){
		result[0] = finalKeyframe[0];
		result[1] = finalKeyframe[1];
	}
	else{
		result[0] = initialKeyframe[0];
		result[1] = initialKeyframe[1];
	}
	float u = float(i)/10;
	for(int j = 2; j < initialKeyframe.size(); j++){
		result[j] = u*initialKeyframe[j] + (1 - u)*finalKeyframe[j];
	}
}

void readFrames(){
	cout << "Reading the frames..." << endl;
	string line;
	ifstream infile;
	infile.open ("keyframes.txt");
	vector<float> initialKeyframe(35, 0);
	vector<float> finalKeyframe(35, 0);
	
	bool setInitialFrame = false;
    while(!infile.eof()){

        getline(infile,line); 
        if(line != ""){
	       	istringstream buf(line);
	       	vector<float> frameValues(35, 0);
	       	for(int i = 0; i < frameValues.size(); i++){
	        	buf >> frameValues[i];
	       	}
	       	if(setInitialFrame){
	       		finalKeyframe = initialKeyframe;
	       		initialKeyframe = frameValues;
	       		for(int i = 1; i <= 50; i++){
	       			vector<float> result(35, 0);
	       			interpolate(initialKeyframe, finalKeyframe, result, i);
	       			frames.push_back(result);
	       		}
	       	}
	       	else{
	       		initialKeyframe = frameValues;
	       		setInitialFrame = true;
	       		frames.push_back(initialKeyframe);
	       	}
	    }
    }
	infile.close();
}

void playback(int t){
	light0 = frames[animationStep][0];
	light1 = frames[animationStep][1];

	outerBox->setTheta(frames[animationStep][2]);
	outerBox->setHeight(frames[animationStep][3]);
	modelHeight = (-outerBox->getTheta()/90 - 1);

	model->hipAngleX = frames[animationStep][4];
	model->hipAngleY = frames[animationStep][5]; 
	model->hipAngleZ = frames[animationStep][6];

	model->stomachAngleX = frames[animationStep][7];
	model->stomachAngleY = frames[animationStep][8];
	model->stomachAngleZ = frames[animationStep][9];

	model->neckAngleX = frames[animationStep][10];
	model->neckAngleY = frames[animationStep][11];
	model->neckAngleZ = frames[animationStep][12];

	model->headAngleX = frames[animationStep][13];
	model->headAngleY = frames[animationStep][14];
	model->headAngleZ = frames[animationStep][15];

	model->chestAngleX = frames[animationStep][16];
	model->chestAngleY = frames[animationStep][17];
	model->chestAngleZ = frames[animationStep][18];

	model->armAngleLeftX = frames[animationStep][19];
	model->armAngleLeftY = frames[animationStep][20];
	model->armAngleLeftZ = frames[animationStep][21];

	model->armAngleRightX = frames[animationStep][22];
	model->armAngleRightY = frames[animationStep][23];
	model->armAngleRightZ = frames[animationStep][24];

	model->elbowAngleLeft = frames[animationStep][25];
	model->elbowAngleRight = frames[animationStep][26];

	model->legAngleLeftX = frames[animationStep][27];
	model->legAngleLeftY = frames[animationStep][28];
	model->legAngleLeftZ = frames[animationStep][29];

	model->legAngleRightX = frames[animationStep][30];
	model->legAngleRightY = frames[animationStep][31];
	model->legAngleRightZ = frames[animationStep][32];

	model->kneeAngleLeft = frames[animationStep][33];
	model->kneeAngleRight = frames[animationStep][34];

	animationStep++;
	if(animationStep < frames.size()){
		glutTimerFunc(10, playback, 0);
	}
	glutPostRedisplay();
}

void animation(){
	frames.clear();
	animationStep = 0;
	readFrames();
	glutTimerFunc(0, playback, 0);
}

void moveLookat(int key, int x, int y){
	if(controlPointFlag){
		switch (key) {
		  	case GLUT_KEY_LEFT :
		  		currentControlPoint->setZCoordinate(currentControlPoint->getZCoordinate() + 0.05);
		  		break;
		  	case GLUT_KEY_RIGHT : 
		  		currentControlPoint->setZCoordinate(currentControlPoint->getZCoordinate() - 0.05);
		  		break;
		  	case GLUT_KEY_UP : 
		  		currentControlPoint->setYCoordinate(currentControlPoint->getYCoordinate() + 0.05);
		  		break;
		  	case GLUT_KEY_DOWN : 
		  		currentControlPoint->setYCoordinate(currentControlPoint->getYCoordinate() - 0.05);
		  		break;
	  	}
	  	glutPostRedisplay();
	}
	else if(!bezierMode){
	  	switch (key) {
		  	case GLUT_KEY_LEFT : 
		  		angle -= 0.1f;
		  		break;
		  	case GLUT_KEY_RIGHT : 
		  		angle +=0.1f;
		  		break;
		  	case GLUT_KEY_UP : 
		  		radius -= 0.1f;
		  		break;
		  	case GLUT_KEY_DOWN : 
		  		radius +=0.1f;
		  		break;
	  	}
	  	camera[0] = radius*cos(angle);
	  	camera[1] = 0.0;
	  	camera[2] = -radius*sin(angle);
	  	modifyLookAt(camera);
	}
}

void keyboard( unsigned char key, int x, int y ) {
	int dir;
    switch(key) {
	    case 27: 
	        exit(0);
	        break;
	    case '7':
	    	//toggle record mode
	    	recordMode = !(recordMode);
	    	if(recordMode){
	    		cout << "Record mode on." << endl;
	    	}
	    	else{
	    		cout << "Record mode off." << endl;
	    	}
	    	break;
	    case '8':
	    	if(recordMode){
	    		Record();
	    		cout << "Frame captured!" << endl;
	    	}
	    	break;
	    case '\'':
	    	animation();
	    case 'O':
	    	if(light1){
	    		glEnable(GL_LIGHT1);
	    	}
	    	else
	    		glDisable(GL_LIGHT1);
	    	light1=!(light1);
	    	break;
	    case 'P':
	    	if(light0){
	    		glEnable(GL_LIGHT0);
	    	}
	    	else
	    		glDisable(GL_LIGHT0);
	    	light0=!(light0);
	    	break;
	    case '9':
	    	timerIndex = 0;
	    	setCameraPath();
	    	break;
	    case '/':
	    	if(controlPointFlag){
		  		currentControlPoint->setXCoordinate(currentControlPoint->getXCoordinate() + 0.05);
		  	}
		  	break;
	  	case '?' : 
	  		if(controlPointFlag){
		  		currentControlPoint->setXCoordinate(currentControlPoint->getXCoordinate() - 0.05);
		  	}
		  	break;
		case '=':
			if(controlPointFlag){
		  		bezier->addControlPoint(currentControlPoint->getXCoordinate(), currentControlPoint->getYCoordinate(), currentControlPoint->getZCoordinate());
		  		controlPointFlag = false;
		  	}
			break;
		case '-':
			if(controlPointFlag){
		  		controlPointFlag = false;
		  	}
			break;
	    case '+':
	    	if(bezierMode){
	    		addControlPointFlag = true;
	    		cout << "Click on the screen to select x and y coordinates of the point" << endl;
	    	}
	    	radius = 30.0;
    		angle = -(M_PI)/2;
    		camera[0] = radius*cos(angle);
    		camera[1] = 0.0;
    		camera[2] = -radius*sin(angle);
    		modifyLookAt(camera);
	    	break;
	    case '0':
	   		//Toggle bezier curve mode
	    	if(bezierMode){
	    		cout << "Bezier mode turned off!" << endl;
	    		bezierMode = false;
	    		radius = 30.0;
	    		angle = -(M_PI)/2;
	    		camera[0] = radius*cos(angle);
	    		camera[1] = 0.0;
	    		camera[2] = -radius*sin(angle);
	    		controlPointFlag = false;
	    		addControlPointFlag = false;
	    		modifyLookAt(camera);

	    	}
	    	else{
	    		cout << "Bezier mode turned on!" << endl;
	    		bezier->setSampling(sampling);
	    		bezierMode = true;
	    		radius = 30.0;
	    		angle = -(M_PI)/2;
	    		camera[0] = radius*cos(angle);
	    		camera[1] = 0.0;
	    		camera[2] = -radius*sin(angle);
	    		modifyLookAt(camera);
	    	}
	    	break;
	    //Rotate Box
	   	case ']':
	   		if(outerBox->getTheta() > -180){
		    	outerBox->setTheta(outerBox->getTheta() - 4);
          		outerBox->setHeight(outerBox->getHeight()+.042);
          		modelHeight = (-outerBox->getTheta()/90 - 1);

		    }
		    break;
	   	case '[':
	   		if(outerBox->getTheta() < 0){
		    	outerBox->setTheta(outerBox->getTheta() + 4);
          		outerBox->setHeight(outerBox->getHeight()-.042);
          		modelHeight = (-outerBox->getTheta()/90 - 1);
		    }
	    	break;

		//Rotate Hip
	    case '$':
	    	dir = -1;
	    	model->rotateHipX(dir);
	    	break;
	    case '4':
	    	dir = 0;
	    	model->rotateHipX(dir);
	    	break;
	    case '%':
	    	dir = -1;
	    	model->rotateHipY(dir);
	    	break;
	    case '5':
	    	dir = 0;
	    	model->rotateHipY(dir);
	    	break;
	    case '^':
	    	dir = -1;
	    	model->rotateHipZ(dir);
	    	break;
	    case '6':
	    	dir = 0;
	    	model->rotateHipZ(dir);
	    	break;
	    	    
	    //Rotate Upper Body
	    case '!':
	    	dir = -1;
	    	model->rotateUpperBodyX(dir);
	    	break;
	    case '1':
	    	dir = 0;
	    	model->rotateUpperBodyX(dir);
	    	break;
	    case '@':
	    	dir = -1;
	    	model->rotateUpperBodyY(dir);
	    	break;
	    case '2':
	    	dir = 0;
	    	model->rotateUpperBodyY(dir);
	    	break;
	    case '#':
	    	dir = -1;
	    	model->rotateUpperBodyZ(dir);
	    	break;
	    case '3':
	    	dir = 0;
	    	model->rotateUpperBodyZ(dir);
	    	break;

		//Rotate Chest
	    case 'J':
	    	dir = -1;
	    	model->rotateChestX(dir);
	    	break;
	    case 'j':
	    	dir = 0;
	    	model->rotateChestX(dir);
	    	break;
	    case 'K':
	    	dir = -1;
	    	model->rotateChestY(dir);
	    	break;
	    case 'k':
	    	dir = 0;
	    	model->rotateChestY(dir);
	    	break;
	    case 'L':
	    	dir = -1;
	    	model->rotateChestZ(dir);
	    	break;
	    case 'l':
	    	dir = 0;
	    	model->rotateChestZ(dir);
	    	break;

		//Rotate Neck
	    case 'F':
	    	dir = -1;
	    	model->rotateHeadPlusNeckX(dir);
	    	break;
	    case 'f':
	    	dir = 0;
	    	model->rotateHeadPlusNeckX(dir);
	    	break;
	    case 'G':
	    	dir = -1;
	    	model->rotateHeadPlusNeckY(dir);
	    	break;
	    case 'g':
	    	dir = 0;
	    	model->rotateHeadPlusNeckY(dir);
	    	break;
	    case 'H':
	    	dir = -1;
	    	model->rotateHeadPlusNeckZ(dir);
	    	break;
	    case 'h':
	    	dir = 0;
	    	model->rotateHeadPlusNeckZ(dir);
	    	break;

	    //Rotate Head
	    case 'A':
	    	dir = -1;
	    	model->rotateHeadX(dir);
	    	break;
	    case 'a':
	    	dir = 0;
	    	model->rotateHeadX(dir);
	    	break;
	    case 'S':
	    	dir = -1;
	    	model->rotateHeadY(dir);
	    	break;
	    case 's':
	    	dir = 0;
	    	model->rotateHeadY(dir);
	    	break;
	    case 'D':
	    	dir = -1;
	    	model->rotateHeadZ(dir);
	    	break;
	    case 'd':
	    	dir = 0;
	    	model->rotateHeadZ(dir);
	    	break;

	    //Rotate left arm (model's left)
	    case 'B':
	    	dir = -1;
	    	model->rotateArmLeftX(dir);
	    	break;
	    case 'b':
	    	dir = 0;
	    	model->rotateArmLeftX(dir);
	    	break;
	    case 'N':
	    	dir = -1;
	    	model->rotateArmLeftY(dir);
	    	break;
	    case 'n':
	    	dir = 0;
	    	model->rotateArmLeftY(dir);
	    	break;
	    case 'M':
	    	dir = -1;
	    	model->rotateArmLeftZ(dir);
	    	break;
	    case 'm':
	    	dir = 0;
	    	model->rotateArmLeftZ(dir);
	    	break;

	    //Rotate left forearm
	    case '<':
	    	dir = -1;
	    	model->rotateElbowAngleLeft(dir);
	    	break;
	    case ',':
	    	dir = 0;
	    	model->rotateElbowAngleLeft(dir);
	    	break;


	    //Rotate right arm (model's right)
	    case 'Z':
	    	dir = -1;
	    	model->rotateArmRightX(dir);
	    	break;
	    case 'z':
	    	dir = 0;
	    	model->rotateArmRightX(dir);
	    	break;
	    case 'X':
	    	dir = -1;
	    	model->rotateArmRightY(dir);
	    	break;
	    case 'x':
	    	dir = 0;
	    	model->rotateArmRightY(dir);
	    	break;
	    case 'C':
	    	dir = -1;
	    	model->rotateArmRightZ(dir);
	    	break;
	    case 'c':
	    	dir = 0;
	    	model->rotateArmRightZ(dir);
	    	break;

	    //Rotate right forearm
	    case 'V':
	    	dir = -1;
	    	model->rotateElbowAngleRight(dir);
	    	break;
	    case 'v':
	    	dir = 0;
	    	model->rotateElbowAngleRight(dir);
	    	break;

		//Rotate left leg (model's left)
	    case 'T':
	    	dir = -1;
	    	model->rotateLegLeftX(dir);
	    	break;
	    case 't':
	    	dir = 0;
	    	model->rotateLegLeftX(dir);
	    	break;
	    case 'Y':
	    	dir = -1;
	    	model->rotateLegLeftY(dir);
	    	break;
	    case 'y':
	    	dir = 0;
	    	model->rotateLegLeftY(dir);
	    	break;
	    case 'U':
	    	dir = -1;
	    	model->rotateLegLeftZ(dir);
	    	break;
	    case 'u':
	    	dir = 0;
	    	model->rotateLegLeftZ(dir);
	    	break;

		//Rotate left kee
	    case 'I':
	    	dir = -1;
	    	model->rotateKneeAngleLeft(dir);
	    	break;
	    case 'i':
	    	dir = 0;
	    	model->rotateKneeAngleLeft(dir);
	    	break;

	    //Rotate right leg (model's Right)
	    case 'Q':
	    	dir = -1;
	    	model->rotateLegRightX(dir);
	    	break;
	    case 'q':
	    	dir = 0;
	    	model->rotateLegRightX(dir);
	    	break;
	    case 'W':
	    	dir = -1;
	    	model->rotateLegRightY(dir);
	    	break;
	    case 'w':
	    	dir = 0;
	    	model->rotateLegRightY(dir);
	    	break;
	    case 'E':
	    	dir = -1;
	    	model->rotateLegRightZ(dir);
	    	break;
	    case 'e':
	    	dir = 0;
	    	model->rotateLegRightZ(dir);
	    	break;

	    //Rotate right knee
	    case 'R':
	    	dir = -1;
	    	model->rotateKneeAngleRight(dir);
	    	break;
	    case 'r':
	    	dir = 0;
	    	model->rotateKneeAngleRight(dir);
	    	break;

	    default:
	        cout << "Key Press" << endl;
	        break;
    }
    glutPostRedisplay();
}

int main (int argc, char *argv[]){

    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(win_width, win_height); //Set the window size

    glutCreateWindow( "Music Box" );
	glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    init();
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutMouseFunc( mouse );  
    glutKeyboardFunc( keyboard );
    glutSpecialFunc(moveLookat);
    glutPostRedisplay();
 
    glutMainLoop();
}
