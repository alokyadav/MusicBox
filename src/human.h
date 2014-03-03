#ifndef HUMAN_T_H_
#define HUMAN_T_H_

#include "cuboid.h"
#include <cmath>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>

using namespace std;

class human {
	private:
		GLUquadric *quad;
		imageLoader* TextImage ;
		GLuint Stexture;
		GLuint Htexture;
		GLuint EyeTexture;
		GLuint BodyTexture;
		vector<GLuint> bodyParts;
	
	public:
		void createLowerArmList();
		void createUpperArmList();
		void createChestList();
		void createNeckList();
		void createStomachList();
		void createHipList();
		void createHeadList();
		void createJointList();
		//Hip
		void drawHip();
		float hipAngleX;
		float hipAngleY;
		float hipAngleZ;
		//Upper Body
		void drawUpperBody();
		//Stomach
		void drawStomach();
		float stomachAngleX;
		float stomachAngleY;
		float stomachAngleZ;
		//Torso
		void drawTorso();
		//Neck plus head
		void drawHeadPlusNeck();
		float neckAngleX;
		float neckAngleY;
		float neckAngleZ;

		//head
		frustum *head;
		float headAngleX;
		float headAngleY;
		float headAngleZ;
		void drawHead();
		//Hat
		void drawHat();
		//eye
		void drawEye();
		//nose
		void drawNose();
		//neck
		cuboid *neck;
		void drawNeck();

		//chest
		void drawChest();
		float chestAngleX;
		float chestAngleY;
		float chestAngleZ;


		//arms
		float armAngleLeftX;
		float armAngleLeftY;
		float armAngleLeftZ;

		float armAngleRightX;
		float armAngleRightY;
		float armAngleRightZ;

		float elbowAngleLeft;
		float elbowAngleRight;

		void drawArm(float elbowAngle);
		void drawLeftArm();
		void drawRightArm();

		//legs
		float legAngleLeftX;
		float legAngleLeftY;
		float legAngleLeftZ;

		float legAngleRightX;
		float legAngleRightY;
		float legAngleRightZ;

		float kneeAngleLeft;
		float kneeAngleRight;

		void drawLeftLeg();
		void drawRightLeg();


		human();
		void draw();

		void init();

		void drawBody();

		void rotateChestX(int dir);
		void rotateChestY(int dir);
		void rotateChestZ(int dir);

		void rotateHeadX(int dir);
		void rotateHeadY(int dir);
		void rotateHeadZ(int dir);

		void rotateHeadPlusNeckX(int dir);
		void rotateHeadPlusNeckY(int dir);
		void rotateHeadPlusNeckZ(int dir);

		void rotateArmLeftX(int dir);
		void rotateArmLeftY(int dir);		
		void rotateArmLeftZ(int dir);

		void rotateArmRightX(int dir);
		void rotateArmRightY(int dir);		
		void rotateArmRightZ(int dir);

		void rotateElbowAngleLeft(int dir);
		void rotateElbowAngleRight(int dir);

		void rotateKneeAngleLeft(int dir);
		void rotateKneeAngleRight(int dir);

		void rotateUpperBodyX(int dir);
		void rotateUpperBodyY(int dir);
		void rotateUpperBodyZ(int dir);

		void rotateHipX(int dir);
		void rotateHipY(int dir);
		void rotateHipZ(int dir);

		void rotateLegLeftX(int dir);
		void rotateLegLeftY(int dir);		
		void rotateLegLeftZ(int dir);

		void rotateLegRightX(int dir);
		void rotateLegRightY(int dir);		
		void rotateLegRightZ(int dir);

};

#endif