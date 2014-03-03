#include "lamp.h"

lamp::lamp(){
	quad= gluNewQuadric();
   	cube = new cuboid();
   	hood=new frustum();
   	image_tex=new imageLoader();
   	lampParts.resize(8);
}
void lamp::Light(){
	
	GLfloat lightpos[] = {0.0, 0.0, 0.0, 1.0f};
	GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		//GLfloat specularLight[] = { .8f, 0.8f, 0.8f, 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);

}
void lamp::init(){
	Texture=image_tex->loadBMP_custom("./textures/lampTop.bmp");
	Skeleton_tex=image_tex->loadBMP_custom("./textures/stand1.bmp");
	gluQuadricTexture(quad,1);
	createList();
}

void lamp::drawSkeleton(){

   //glColor3f(1.0f,0.0f,0.0f);
	glPushMatrix();
	glCallList(lampParts[0]);
	glPopMatrix();
	glPushMatrix();
	glCallList(lampParts[1]);
	glPopMatrix();
	glPushMatrix();
	glCallList(lampParts[2]);
	glPopMatrix();
	glPushMatrix();
	glCallList(lampParts[3]);
	glPopMatrix();
	//glColor3f(1.0f,1.0f,1.0f);
	glPushMatrix();
	glCallList(lampParts[4]);
	glPopMatrix();

	glPushMatrix();
	glCallList(lampParts[5]);
	glPopMatrix();
	glPushMatrix();
	glRotatef(240.0f,0.0f,0.0f,1.0f);
	glCallList(lampParts[5]);
	glPopMatrix();
	glPushMatrix();
	glRotatef(120.0f,0.0f,0.0f,1.0f);
	glCallList(lampParts[5]);
	glPopMatrix();

	glPushMatrix();
	glCallList(lampParts[6]);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180.0f,1.0f,0.0f,0.0f);
	glScalef(2.0f,2.0f,2.0f);
	glCallList(lampParts[7]);
	glPopMatrix();
}


void lamp::drawCylinder(float radiusU,float radiusL, float height){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->Skeleton_tex);
	gluQuadricOrientation(quad,GLU_INSIDE);
   	gluDisk(quad, 0.0, radiusL, 100, 15);
   	gluQuadricOrientation(quad,GLU_OUTSIDE);
   	gluCylinder(quad,radiusL ,radiusU,height,100,32);
   	glPushMatrix();
   	glTranslatef(0.0f,0.0f,height);
   	gluQuadricOrientation(quad,GLU_OUTSIDE);
   	gluDisk(quad, 0.0f, radiusU, 100, 15);
   	glPopMatrix();
   	glDisable(GL_TEXTURE_2D);

}
void lamp::drawRing(float innerR,float outerR,float thickness){
	glEnable(GL_TEXTURE_2D);
   	glBindTexture(GL_TEXTURE_2D, this->Texture);
	gluQuadricOrientation(quad,GLU_INSIDE);
	gluDisk(quad,innerR, outerR, 100, 15);
	gluQuadricOrientation(quad,GLU_OUTSIDE);
   	gluCylinder(quad,outerR ,outerR,thickness,100,32);
   	gluQuadricOrientation(quad,GLU_INSIDE);
   	gluCylinder(quad,innerR ,innerR,thickness,100,32);
   	glPushMatrix();
   	glTranslatef(0.0f,0.0f,thickness);
   	gluQuadricOrientation(quad,GLU_OUTSIDE);
   	gluDisk(quad,innerR, outerR, 100, 15);
   	glPopMatrix();	
   	glDisable(GL_TEXTURE_2D);

}


void lamp::drawTop(float radiusU ,float radiusL , float height ,float thickness){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->Skeleton_tex);
   		glBindTexture(GL_TEXTURE_2D, this->Texture);
		gluQuadricOrientation(quad,GLU_INSIDE);
		gluDisk(quad, radiusL+thickness, radiusL+thickness, 100, 15);
		gluQuadricOrientation(quad,GLU_INSIDE);
		gluCylinder(quad,radiusL+thickness ,radiusU+thickness,height,100,32);
		gluQuadricOrientation(quad,GLU_INSIDE);
		gluCylinder(quad,radiusL-thickness ,radiusU-thickness,height,100,32);
		glPushMatrix();
   			glTranslatef(0.0f,0.0f,height);
   			gluQuadricOrientation(quad,GLU_OUTSIDE);
   			gluDisk(quad, radiusU-thickness, radiusU+thickness, 100, 15);
   		glPopMatrix();
   		glDisable(GL_TEXTURE_2D);

}
void lamp::drawBulb(){
	gluQuadricOrientation(quad,GLU_INSIDE);
	gluSphere(quad,1,20,20);
}

void lamp::drawlampTable(){

	drawRing(0,2.0,.2);
	glPushMatrix();
	glTranslatef(.8f,.8f,.2f);
	drawRing(0.0,0.2,2.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-.8f,-.8f,.2f);
	drawRing(0.0,0.2,2.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-.8f,.8f,.2f);
	drawRing(0.0,0.2,2.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(.8f,-.8f,.2f);
	drawRing(0.0,0.2,2.5);
	glPopMatrix();
}

void lamp::createList(){
	lampParts[0] = glGenLists(1);
   	glNewList(lampParts[0], GL_COMPILE);
   	drawCylinder(1.6,1.8,.25);
   	glEndList();
   	lampParts[1] = glGenLists(1);
   	glNewList(lampParts[1], GL_COMPILE);
   	glTranslatef(0.0f,0.0f,.25f);
	drawCylinder(.25f,.25f,6.0f);
   	glEndList();

   	lampParts[2] = glGenLists(1);
   	glNewList(lampParts[2], GL_COMPILE);
 	glTranslatef(0.0f,0.0f,6.25f);
	drawRing(.25,.45,.2);
   	glEndList();

   	lampParts[3] = glGenLists(1);
   	glNewList(lampParts[3], GL_COMPILE);
   	glTranslatef(0.0f,0.0f,7.00f);
	drawRing(.65,.85,.2);
   	glEndList();

   	lampParts[4] = glGenLists(1);
   	glNewList(lampParts[4], GL_COMPILE);
   	glTranslatef(0.0f,0.0f,7.2f);
   	Light();
	glScalef(.5f,.5f,.5f);
	drawBulb();
   	glEndList();

   	lampParts[5] = glGenLists(1);
   	glNewList(lampParts[5], GL_COMPILE);
   	glTranslatef(0.35f,0.0f,6.35f);
	glRotatef(28.070f,0.0f,1.0f,0.0f);
	drawCylinder(.05,.05,2);
   	glEndList();

   	lampParts[6] = glGenLists(1);
   	glNewList(lampParts[6], GL_COMPILE);
   	glTranslatef(0.0f,0.0f,6.115f);
	drawTop(1.291,1.291,2.5,.05);
   	glEndList();

   	lampParts[7] = glGenLists(1);
   	glNewList(lampParts[7], GL_COMPILE);
   	drawlampTable();
   	glEndList();
}