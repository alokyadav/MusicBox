#include "human.h"

using namespace std;

human::human(){
	quad = gluNewQuadric();
	bodyParts.resize(8);
	TextImage=new imageLoader();
	
	//Neck plus chest

	neckAngleX = 0.0;
	neckAngleY = 0.0;
	neckAngleZ = 0.0;

	//Head
	headAngleX = -10.0;
	headAngleY = 0.0;
	headAngleZ = 10.0;
	head = new frustum();

	//Neck
	neck = new cuboid();

	//Chest
	chestAngleX = 0.0;
	chestAngleY = 0.0;
	chestAngleZ = 0.0;

	//hip
	stomachAngleX = 0.0;
	stomachAngleY = 0.0;
	stomachAngleZ = 0.0;

	//Hip
	hipAngleX = 0.0;
	hipAngleY = 0.0;
	hipAngleZ = 0.0;

	//Arm
	elbowAngleLeft = 0.0;
	elbowAngleRight = -120.0;

	armAngleLeftX = 0.0;
	armAngleLeftY = 0.0;
	armAngleLeftZ = 30.0;

	armAngleRightX = 0.0;
	armAngleRightY = 0.0;
	armAngleRightZ = 30.0;

	//Leg
	kneeAngleLeft = 0.0;
	kneeAngleRight = 0.0;

	legAngleLeftX = 0.0;
	legAngleLeftY = 0.0;
	legAngleLeftZ = 0.0;

	legAngleRightX = 0.0;
	legAngleRightY = 0.0;
	legAngleRightZ = 0.0;

}

void human::init(){
	Stexture=TextImage->loadBMP_custom("./textures/limb.bmp");
	this->Htexture = TextImage->loadBMP_custom("./textures/body.bmp");
	EyeTexture=TextImage->loadBMP_custom("./textures/eye.bmp");
	BodyTexture=TextImage->loadBMP_custom("./textures/body.bmp");
	createHeadList();
	createHipList();
	createStomachList();
	createNeckList();
	createChestList();
	createUpperArmList();
	createLowerArmList();
	createJointList();
}

void human::draw(){
	glTranslatef(0.0f, 0.0f, 0.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	drawBody();
}

void human::drawBody(){
	glPushMatrix();
		glRotatef(hipAngleX, 1.0f, 0.0f, 0.0f);
		glRotatef(hipAngleY, 0.0f, 1.0f, 0.0f);
		glRotatef(hipAngleZ, 0.0f, 0.0f, 1.0f);
		drawUpperBody();
		drawHip();
		glPushMatrix();
			glTranslatef(0.0f, -5.0f, 0.0f);
			drawLeftLeg();
			drawRightLeg();
		glPopMatrix();
	glPopMatrix();	
}

void human::createHipList(){
	bodyParts[0] = glGenLists(1);
	glNewList(bodyParts[0], GL_COMPILE);
		glTranslatef(0.0f, -6.2f, 0.0f);
		glScalef(1.0f,0.5f ,0.75f);
		head->setTexture(BodyTexture);
		head->draw();
	glEndList();
}


void human::drawHip(){
	glPushMatrix();
		glCallList(bodyParts[0]);
	glPopMatrix();
}

void human::drawUpperBody(){
	glPushMatrix();
		glTranslatef(0.0f, -5.0f, 0.0f);
		glRotatef(stomachAngleX, 1.0f, 0.0f, 0.0f);
		glRotatef(stomachAngleY, 0.0f, 1.0f, 0.0f);
		glRotatef(stomachAngleZ, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 5.0f, 0.0f);
		drawTorso();
		drawStomach();
	glPopMatrix();
}

void human::drawTorso(){
	glPushMatrix();
		glRotatef(chestAngleX, 1.0f, 0.0f, 0.0f);
		glRotatef(chestAngleY, 0.0f, 1.0f, 0.0f);
		glRotatef(chestAngleZ, 0.0f, 0.0f, 1.0f);
		drawHeadPlusNeck();	
		drawLeftArm();
		drawRightArm();
		drawChest();
	glPopMatrix();
}

void human::createStomachList(){
	bodyParts[1] = glGenLists(1);
	glNewList(bodyParts[1], GL_COMPILE);
		glTranslatef(0.0f, -5.1f, 0.0f);
		glScalef(1.0f,0.5f ,0.75f);
		neck->setTexture(Stexture);
		neck->draw();
	glEndList();
}

void human::drawStomach(){
	glPushMatrix();
		glCallList(bodyParts[1]);
	glPopMatrix();
}

void human::drawHeadPlusNeck(){
	glPushMatrix();
		glRotatef(neckAngleX, 1.0f, 0.0f, 0.0f);
		glRotatef(neckAngleY, 0.0f, 1.0f, 0.0f);
		glRotatef(neckAngleZ, 0.0f, 0.0f, 1.0f);
		drawHead();
		drawNeck();
	glPopMatrix();
}

void human::drawHead(){
	glPushMatrix();	
		glRotatef(headAngleX, 1.0f, 0.0f, 0.0f);
		glRotatef(headAngleY, 0.0f, 1.0f, 0.0f);
		glRotatef(headAngleZ, 0.0f, 0.0f, 1.0f);
		glCallList(bodyParts[6]);
	glPopMatrix();	
}
void human::createHeadList(){
	bodyParts[6] = glGenLists(1);
	glNewList(bodyParts[6], GL_COMPILE);	
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
		glScalef(0.75f, 1.0f, 0.75f);
		drawHat();
		glPushMatrix();
		glTranslatef(-0.6f,-0.5f,-2.0f);
		drawEye();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.6f,-0.5f,-2.0f);
		drawEye();
		glPopMatrix();
		drawNose();
		head->setTexture(BodyTexture);
		head->draw();	
	glEndList();

}
void human::createNeckList(){
	bodyParts[2] = glGenLists(1);
	glNewList(bodyParts[2], GL_COMPILE);
		glTranslatef(0.0f, -1.25f, 0.0f);
		glScalef(0.75f, 0.25f, 1.0f);
		neck->setTexture(Stexture);
		neck->draw();
	glEndList();
}

void human::drawNeck(){
	glPushMatrix();	
		glCallList(bodyParts[2]);
	glPopMatrix();	
}

void human::createChestList(){
	bodyParts[3] = glGenLists(1);
	glNewList(bodyParts[3], GL_COMPILE);
		
		glTranslatef(0.0f, -3.0f, 0.0f);
		glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
		glScalef(1.0f, 1.5f, 0.75f);
		head->setTexture(BodyTexture);
		head->draw();
	glEndList();
}

void human::drawChest(){
	glPushMatrix();
		glCallList(bodyParts[3]);
	glPopMatrix();	
}

void human::createUpperArmList(){
	bodyParts[4] = glGenLists(1);
	glNewList(bodyParts[4], GL_COMPILE);
		glScalef(1.7f, 0.5f, 0.5f);
		neck->setTexture(Stexture);
		neck->draw();
	glEndList();
}

void human::createLowerArmList(){
	bodyParts[5] = glGenLists(1);
	glNewList(bodyParts[5], GL_COMPILE);
		glTranslatef(-2.05f, 0.0f, 0.0f);
		glTranslatef(3.75f, 0.0f, 0.0f);
		glPushMatrix();
			glScalef(1.7f, 0.4f, 0.4f);
			neck->setTexture(Stexture);
			neck->draw();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.6f, 0.0f, 0.0f);
			gluSphere(quad,0.5,20,20);
		glPopMatrix();
	glEndList();
}
void human::createJointList(){
	bodyParts[7] = glGenLists(1);
	glNewList(bodyParts[7], GL_COMPILE);
		glScalef(1.0f, 0.75f, 1.0f);
		gluSphere(quad,0.5,20,20);
	glEndList();
	
}


void human::drawArm(float elbowAngle){
	glPushMatrix();
		glPushMatrix();
			
			glCallList(bodyParts[7]);
		glPopMatrix();
		glTranslatef(2.0f, 0.0f, 0.0f);
		//Upper Arm
    	

		glPushMatrix();	
			glCallList(bodyParts[4]);
		glPopMatrix();

		//Lower Arm
		glPushMatrix();
			glTranslatef(2.05f, 0.0f, 0.0f);
			glPushMatrix();
				glScalef(1.0f, 0.75f, 1.0f);
				glCallList(bodyParts[7]);
			glPopMatrix();
			glRotatef(elbowAngle, 0.0f, 1.0f, 0.0f);	
			glCallList(bodyParts[5]);
		glPopMatrix();
	glPopMatrix();
}

void human::drawLeftArm(){
	glPushMatrix();		
		glTranslatef(2.25f, -1.75f, 0.0f);
		glRotatef(armAngleLeftX, 1.0f, 0.0f, 0.0f);
		glRotatef(armAngleLeftY, 0.0f, 1.0f, 0.0f);
		glRotatef(armAngleLeftZ, 0.0f, 0.0f, 1.0f);		
		glScalef(1.0f, 0.75f, 0.75f);
		drawArm(elbowAngleLeft);
	glPopMatrix();
}

void human::drawLeftLeg(){
	glPushMatrix();
		glTranslatef(1.65f, -1.75f, 0.0f);
		glRotatef(legAngleLeftX, 1.0f, 0.0f, 0.0f);
		glRotatef(legAngleLeftY, 0.0f, 1.0f, 0.0f);
		glRotatef(legAngleLeftZ, 0.0f, 0.0f, 1.0f);
		glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
		drawArm(kneeAngleLeft);
	glPopMatrix();
}
void human::drawRightArm(){
	glPushMatrix();
		glTranslatef(-2.25f, -1.75f, 0.0f);
		glRotatef(armAngleRightX, 1.0f, 0.0f, 0.0f);
		glRotatef(armAngleRightY, 0.0f, 1.0f, 0.0f);
		glRotatef(armAngleRightZ, 0.0f, 0.0f, 1.0f);
		glScalef(-1.0f, 0.75f, 0.75f);
		drawArm(elbowAngleRight);
	glPopMatrix();
}

void human::drawRightLeg(){
	glPushMatrix();
		glTranslatef(-1.65f, -1.75f, 0.0f);
		glRotatef(legAngleRightX, 1.0f, 0.0f, 0.0f);
		glRotatef(legAngleRightY, 0.0f, 1.0f, 0.0f);
		glRotatef(legAngleRightZ, 0.0f, 0.0f, 1.0f);
		glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
		drawArm(kneeAngleRight);
	glPopMatrix();
}
void human::drawHat(){  
	glPushMatrix();	
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->Htexture);
    gluQuadricDrawStyle(quad, GLU_FILL);
    glTranslatef(0.0f,-.70f,0.0f);   
    glRotatef(8.0,0.0f,0.0f,1.0f); 
    glRotatef(90.0,1.0f,0.0f,0.0f);
    glScalef(1.0f,1.0f,0.75f);
    gluQuadricTexture(quad,1);
    gluCylinder(quad,3.0f,2.0f,1.75f,32,32);
    gluDisk(quad, 3.0, 4.5, 15, 15);
    glPushMatrix();
    glTranslatef(0.0f,0.0f,1.5f);
    gluDisk(quad, 0.0, 2.0, 15, 15); 
    glPopMatrix();
    glDisable(GL_TEXTURE_2D); 
    glPopMatrix();
}
void human::drawEye(){
	glPushMatrix();
	gluQuadricDrawStyle(quad, GLU_FILL);
	glScalef(0.6f,0.6f,0.6f);
	gluCylinder(quad,.5f,.5f,.5f,32,32);
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->EyeTexture);
    gluDisk(quad, 0.0, .5f, 15, 15); 
    glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
}
void human::drawNose(){
	glPushMatrix();
		glTranslatef(0.0f,-0.0f,-1.5f);
		glRotatef(-30.0f,1.0f,0.0f,0.0f);
		glScalef(0.15f,0.3f,0.3f);
		neck->setTexture(BodyTexture);
		neck->draw();
	glPopMatrix();
}

void human::rotateElbowAngleLeft(int dir){
	if(dir == 0){
		if(elbowAngleLeft < 0){		
			elbowAngleLeft += 4.0;
		}
	}
	else{
		if(elbowAngleLeft > -120){
			elbowAngleLeft -= 4.0;
		}
	}
}

void human::rotateKneeAngleLeft(int dir){
	if(dir == 0){
		if(kneeAngleLeft < 90){		
			kneeAngleLeft += 4.0;
		}
	}
	else{
		if(kneeAngleLeft > 0){
			kneeAngleLeft -= 4.0;
		}
	}
}

void human::rotateElbowAngleRight(int dir){
	if(dir == 0){
		if(elbowAngleRight < 0){		
			elbowAngleRight += 4.0;
		}
	}
	else{
		if(elbowAngleRight > -120){
			elbowAngleRight -= 4.0;
		}
	}
}

void human::rotateKneeAngleRight(int dir){
	if(dir == 0){
		if(kneeAngleRight < 90){		
			kneeAngleRight += 4.0;
		}
	}
	else{
		if(kneeAngleRight > 0){
			kneeAngleRight -= 4.0;
		}
	}
}

void human::rotateHeadX(int dir){
	if(dir == 0){
		if(headAngleX < 10){		
			headAngleX += 4.0;
		}
	}
	else{
		if(headAngleX > -10){
			headAngleX -= 4.0;
		}
	}
}

void human::rotateHeadY(int dir){
	if(dir == 0){
		if(headAngleY< 30){		
			headAngleY += 4.0;
		}
	}
	else{
		if(headAngleY > -30){
			headAngleY -= 4.0;
		}
	}
}

void human::rotateHeadZ(int dir){
	if(dir == 0){
		if(headAngleZ < 10){		
			headAngleZ += 4.0;
		}
	}
	else{
		if(headAngleZ > -10){
			headAngleZ -= 4.0;
		}
	}
}

void human::rotateHeadPlusNeckX(int dir){
	if(dir == 0){
		if(neckAngleX < 10){		
			neckAngleX += 4.0;
		}
	}
	else{
		if(neckAngleX > -10){
			neckAngleX -= 4.0;
		}
	}
}

void human::rotateHeadPlusNeckY(int dir){
	if(dir == 0){
		if(neckAngleY< 30){		
			neckAngleY += 4.0;
		}
	}
	else{
		if(neckAngleY > -30){
			neckAngleY -= 4.0;
		}
	}
}

void human::rotateHeadPlusNeckZ(int dir){
	if(dir == 0){
		if(neckAngleZ < 10){		
			neckAngleZ += 4.0;
		}
	}
	else{
		if(neckAngleZ > -10){
			neckAngleZ -= 4.0;
		}
	}
}

void human::rotateArmLeftX(int dir){
	if(dir == 0){
		if(armAngleLeftX < 360){		
			armAngleLeftX += 4.0;
		}
	}
	else{
		if(armAngleLeftX > -360){
			armAngleLeftX -= 4.0;
		}
	}
}

void human::rotateArmLeftY(int dir){
	if(dir == 0){
		if(armAngleLeftY < 90){		
			armAngleLeftY += 4.0;
		}
	}
	else{
		if(armAngleLeftY > -90){
			armAngleLeftY -= 4.0;
		}
	}
}

void human::rotateArmLeftZ(int dir){
	if(dir == 0){
		if(armAngleLeftZ < 90){		
			armAngleLeftZ += 4.0;
		}
	}
	else{
		if(armAngleLeftZ > -90){
			armAngleLeftZ -= 4.0;
		}
	}
}


void human::rotateArmRightX(int dir){
	if(dir == 0){
		if(armAngleRightX < 360){		
			armAngleRightX += 4.0;
		}
	}
	else{
		if(armAngleRightX > -360){
			armAngleRightX -= 4.0;
		}
	}
}

void human::rotateArmRightY(int dir){
	if(dir == 0){
		if(armAngleRightY < 90){		
			armAngleRightY += 4.0;
		}
	}
	else{
		if(armAngleRightY > -90){
			armAngleRightY -= 4.0;
		}
	}
}

void human::rotateArmRightZ(int dir){
	if(dir == 0){
		if(armAngleRightZ < 90){		
			armAngleRightZ += 4.0;
		}
	}
	else{
		if(armAngleRightZ > -90){
			armAngleRightZ -= 4.0;
		}
	}
}

void human::rotateLegLeftX(int dir){
	if(dir == 0){
		if(legAngleLeftX < 30){		
			legAngleLeftX += 4.0;
		}
	}
	else{
		if(legAngleLeftX > -120){
			legAngleLeftX -= 4.0;
		}
	}
}

void human::rotateLegLeftY(int dir){
	if(dir == 0){
		if(legAngleLeftY < 45){		
			legAngleLeftY += 4.0;
		}
	}
	else{
		if(legAngleLeftY > -45){
			legAngleLeftY -= 4.0;
		}
	}
}

void human::rotateLegLeftZ(int dir){
	if(dir == 0){
		if(legAngleLeftZ < 45){		
			legAngleLeftZ += 4.0;
		}
	}
	else{
		if(legAngleLeftZ > -45){
			legAngleLeftZ -= 4.0;
		}
	}
}


void human::rotateLegRightX(int dir){
	if(dir == 0){
		if(legAngleRightX < 30){		
			legAngleRightX += 4.0;
		}
	}
	else{
		if(legAngleRightX > -120){
			legAngleRightX -= 4.0;
		}
	}
}

void human::rotateLegRightY(int dir){
	if(dir == 0){
		if(legAngleRightY < 45){		
			legAngleRightY += 4.0;
		}
	}
	else{
		if(legAngleRightY > -45){
			legAngleRightY -= 4.0;
		}
	}
}

void human::rotateLegRightZ(int dir){
	if(dir == 0){
		if(legAngleRightZ < 45){		
			legAngleRightZ += 4.0;
		}
	}
	else{
		if(legAngleRightZ > -45){
			legAngleRightZ -= 4.0;
		}
	}
}

void human::rotateChestX(int dir){
	if(dir == 0){
		if(chestAngleX < 10){		
			chestAngleX += 4.0;
		}
	}
	else{
		if(chestAngleX > -10){
			chestAngleX -= 4.0;
		}
	}
}

void human::rotateChestY(int dir){
	if(dir == 0){
		if(chestAngleY< 30){		
			chestAngleY += 4.0;
		}
	}
	else{
		if(chestAngleY > -30){
			chestAngleY -= 4.0;
		}
	}
}

void human::rotateChestZ(int dir){
	if(dir == 0){
		if(chestAngleZ < 10){		
			chestAngleZ += 4.0;
		}
	}
	else{
		if(chestAngleZ > -10){
			chestAngleZ -= 4.0;
		}
	}
}

void human::rotateUpperBodyX(int dir){
	if(dir == 0){
		if(stomachAngleX < 10){		
			stomachAngleX += 4.0;
		}
	}
	else{
		if(stomachAngleX > -10){
			stomachAngleX -= 4.0;
		}
	}
}

void human::rotateUpperBodyY(int dir){
	if(dir == 0){
		if(stomachAngleY< 30){		
			stomachAngleY += 4.0;
		}
	}
	else{
		if(stomachAngleY > -30){
			stomachAngleY -= 4.0;
		}
	}
}

void human::rotateUpperBodyZ(int dir){
	if(dir == 0){
		if(stomachAngleZ < 10){		
			stomachAngleZ += 4.0;
		}
	}
	else{
		if(stomachAngleZ > -10){
			stomachAngleZ -= 4.0;
		}
	}
}

void human::rotateHipX(int dir){
	if(dir == 0){
		if(hipAngleX < 10){		
			hipAngleX += 4.0;
		}
	}
	else{
		if(hipAngleX > -10){
			hipAngleX -= 4.0;
		}
	}
}

void human::rotateHipY(int dir){
	if(dir == 0){
		if(hipAngleY< 30){		
			hipAngleY += 4.0;
		}
	}
	else{
		if(hipAngleY > -30){
			hipAngleY -= 4.0;
		}
	}
}

void human::rotateHipZ(int dir){
	if(dir == 0){
		if(hipAngleZ < 10){		
			hipAngleZ += 4.0;
		}
	}
	else{
		if(hipAngleZ > -10){
			hipAngleZ -= 4.0;
		}
	}
}

