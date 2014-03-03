# include "furniture.h"


furniture::furniture(){
	Table=new table();
	Chair=new chair();
	Lamp =new lamp();
	platForm=new cuboid();
	image_tex= new imageLoader();
	furnitureParts.resize(6);
	doorAngle=45.0f;
	quad= gluNewQuadric();
}
void furniture::Light(){

	GLfloat lightpos[] = {0.0, 0.0, 0.0, 1.0f};
	GLfloat ambientLight[] = { .2f, .2f, .2f, .2f };
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 0.2f };
	GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
}
void furniture::init(){
	Table->init();
	Chair->init();
	Lamp->init();
	Texture=image_tex->loadBMP_custom("./textures/floor.bmp");
	DoorTexture = image_tex->loadBMP_custom("./textures/door.bmp");
	AlmTexture=image_tex->loadBMP_custom("./textures/almirah1.bmp");
	AlmDoorTexture=image_tex->loadBMP_custom("./textures/almirah.bmp");
	gluQuadricDrawStyle(quad, GLU_FILL);
   	gluQuadricTexture(quad,1);
	drawPlatform();
	createDoor();
	createAlmirah();
	createCeilLight();
	createalmirahDoor1();
	createalmirahDoor2();
	

}

void furniture::drawRightWall(){
	glPushMatrix();
	glTranslatef(9.5f,5.0f,0.0f);
	glRotatef(90.0f,0.0f,0.0f,1.0f);
	glScalef(.5f,1.0f,1.0f);
	glCallList(furnitureParts[0]);
	glPopMatrix();
}


void furniture::drawPlatform(){

	furnitureParts[0] = glGenLists(1);
    glNewList(furnitureParts[0], GL_COMPILE);
	//glPushMatrix();
	glScalef(10.0f,0.5f,10.0f);
	platForm->setTexture(Texture);
	platForm->draw();
	//glPopMatrix();
	glEndList();
}

void furniture::createDoor(){
      furnitureParts[1] = glGenLists(1);
      glNewList(furnitureParts[1], GL_COMPILE);
            glTranslatef(3.0f, 4.25f, 0.0f);
            glRotatef(90.0f,1.0f,0.0f,0.0f);
            glScalef(3.0f,.1f, 3.75f);
            platForm->setTexture(DoorTexture);
            platForm->draw();
      glEndList();
}


void furniture::drawDoor(){
      glPushMatrix();
      		glTranslatef(-9.0f, 0.0f, 10.0f);
            glRotatef(doorAngle, 0.0f, 1.0f, 0.0f);      
            glCallList(furnitureParts[1]);
      glPopMatrix();   
}

void furniture::createAlmirah(){
	platForm->setTexture(AlmTexture);
	furnitureParts[2] = glGenLists(1);
	glNewList(furnitureParts[2], GL_COMPILE);
	//base
	glPushMatrix();
	glScalef(1.8f,.1f,1.2f);
	platForm->draw();
	glPopMatrix();
	//top
	glPushMatrix();
	glTranslatef(0.0f, 4.8f, 0.0f);
	glScalef(1.8f,.1f,1.2f);
	platForm->draw();
	glPopMatrix();
	//left
	glPushMatrix();
	glTranslatef(-1.7f, 2.4f, 0.1f);
	glScalef(.1f,2.4f,1.1f);
	platForm->draw();
	glPopMatrix();
	//right
	glPushMatrix();
	glTranslatef(1.7f, 2.4f, .1f);
	glScalef(.1f,2.4f,1.1f);
	platForm->draw();
	glPopMatrix();
	//back
	glPushMatrix();
	glTranslatef(0.0f, 2.4f, 1.1f);
	glScalef(1.8f,2.3f,.1f);
	platForm->draw();
	glPopMatrix();


	platForm->setTexture(AlmDoorTexture);
	glPushMatrix();
	glTranslatef(0.0f, 1.2f, 0.0f);
	glScalef(1.6f,0.1f,1.0f);
	platForm->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 2.4f, 0.0f);
	glScalef(1.6f,0.1f,1.0f);
	platForm->draw();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0f, 3.6f, 0.0f);
	glScalef(1.6f,0.1f,1.0f);
	platForm->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.2f, -.3f, 0.0f);
	glScalef(.2f,0.2f,1.2f);
	platForm->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.2f, -.3f, 0.0f);
	glScalef(.2f,0.2f,1.2f);
	platForm->draw();
	glPopMatrix();

	glEndList();



}
void furniture::drawAlmirah(){


	glPushMatrix();
	glRotatef(180,0.0f,1.0f,0.0f);
	glCallList(furnitureParts[2]);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1.6f, 0.1f, 1.0f);
	glRotatef(-60.0f,0.0f,1.0f,0.0f);
	glCallList(furnitureParts[3]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.6f, 0.1f, 1.0f);
	glRotatef(0.0f,0.0f,1.0f,0.0f);
	glCallList(furnitureParts[4]);
	glPopMatrix();


}

void furniture::createalmirahDoor1(){

	furnitureParts[3] = glGenLists(1);
	glNewList(furnitureParts[3], GL_COMPILE);
	glPushMatrix();
	glTranslatef(0.8f, 2.3f, 0.0f);

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->AlmTexture);
	gluQuadricOrientation(quad,GLU_OUTSIDE);
	glTranslatef(-.8f, 2.3f, 0.0f);
	glRotatef(90.0f,1.0f,0.0f,0.0f);
   	gluCylinder(quad,.05f,.05f,4.6f,100,32);
   	glDisable(GL_TEXTURE_2D);
   	glPopMatrix();


   	glPushMatrix();
	//glTranslatef(1.2f, -.3f, 0.0f);
	glScalef(.75f,2.3f,.1f);
	platForm->draw();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.6f,-.1f,0.1f);
	drawHandle();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.80f, 0.0f, -0.05f);
	glScalef(.05f,2.3f,.05f);
	platForm->draw();
	glPopMatrix();

	glPopMatrix();
	glEndList();

}



void furniture::createalmirahDoor2(){
	furnitureParts[4] = glGenLists(1);
	glNewList(furnitureParts[4], GL_COMPILE);

	glPushMatrix();
	glTranslatef(-0.8f, 2.3f, 0.0f);

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
  	glBindTexture(GL_TEXTURE_2D, this->AlmTexture);
  	gluQuadricOrientation(quad,GLU_OUTSIDE);
	glTranslatef(0.8f, 2.3f, 0.0f);
	glRotatef(90.0f,1.0f,0.0f,0.0f);
   	gluCylinder(quad,.05f,.05f,4.6f,100,32);
   	glDisable(GL_TEXTURE_2D);
   	glPopMatrix();


   	platForm->setTexture(AlmDoorTexture);
	glPushMatrix();
	//glTranslatef(1.2f, -.3f, 0.0f);
	glScalef(.75f,2.3f,.1f);
	//platForm->setTexture(AlmTexture);
	platForm->draw();
	glPopMatrix();
   
   
	glPushMatrix();
	glTranslatef(-.6f,-.1f,0.1f);
	drawHandle();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.80f, 0.0f, 0.05f);
	glScalef(.05f,2.3f,.05f);
	platForm->draw();
	glPopMatrix();

	glPopMatrix();
	glEndList();

}


void furniture::drawHandle(){


	glEnable(GL_TEXTURE_2D);
  	glBindTexture(GL_TEXTURE_2D, this->AlmDoorTexture);
	glPushMatrix();	
   	gluCylinder(quad,.05f,.05f,.1f,32,32);
   	glPopMatrix();
   	glPushMatrix();
  	glTranslatef(0.0f, 0.4f, 0.0f);
   	gluCylinder(quad,.05f,.05f,.1f,32,32);
   	glPopMatrix();
   	glDisable(GL_TEXTURE_2D);
   	glPushMatrix();
   	glTranslatef(0.0f, 0.2f, 0.1f);
   	glScalef(.06f,0.3f,.05f);
	platForm->draw();
   	glPopMatrix();

}
void furniture::createCeilLight(){

	furnitureParts[5] = glGenLists(1);
	glNewList(furnitureParts[5], GL_COMPILE);
	gluQuadricOrientation(quad,GLU_INSIDE);
	glPushMatrix();
	glRotatef(90.0f,1.0f,0.0f,0.0f);
	gluCylinder(quad,0.0f,.6f,.4f,32,32);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.4f);
	gluCylinder(quad,.6f,.6f,1.0f,32,32);
	glPopMatrix();
	glPopMatrix();
	glEndList();

}

void furniture::drawInterior(){

	glPushMatrix();
	glScalef(1.1f,1.0f,1.1f);
	glCallList(furnitureParts[0]);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9.5f,5.0f,0.0f);
	glRotatef(90.0f,0.0f,0.0f,1.0f);
	glScalef(.5f,1.0f,1.0f);
	glCallList(furnitureParts[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,5.0f,-10.0f);
	glRotatef(90.0f,1.0f,0.0f,0.0f);
	glScalef(1.0f,1.0f,.5f);
	glCallList(furnitureParts[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0f,5.0f,10.0f);
	glRotatef(90.0f,1.0f,0.0f,0.0f);
	glScalef(.7f,1.0f,.5f);
	glCallList(furnitureParts[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7.0f,9.0f,10.0f);
	glRotatef(90.0f,1.0f,0.0f,0.0f);
	glScalef(.3f,1.0f,.1f);
	glCallList(furnitureParts[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,10.0f,0.0f);

	glPushMatrix();
	glTranslatef(0.0f,-.6f,0.0f);

	glCallList(furnitureParts[5]);

	glPushMatrix();
	glTranslatef(0.0f,-.8f,0.0f);
	Light();
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glScalef(1.1f,1.0f,1.1f);
	glCallList(furnitureParts[0]);
	glPopMatrix();
	glPopMatrix();


	drawDoor();

	glPushMatrix();
	glTranslatef(7.5f,2.2f,7.5f);
	//Chair->drawChair();
	glRotatef(-90.0f,1.0f,0.0f,0.0f);
	glScalef(.33f,.33f,.33f);
	Lamp->drawSkeleton();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f,1.72f,.0f);
	glScalef(.5f,.5f,.5f);
	glPushMatrix();
	glTranslatef(0.0f,1.4f,0.0f);
	Table->drawTable();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-10.0f, 0.0f, 0.0f);
	glRotatef(90.0f,0.0f,1.0f,0.0f);
	Chair->drawChair();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10.0f, 0.0f, 0.0f);
	glRotatef(-90.0f,0.0f,1.0f,0.0f);
	Chair->drawChair();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 10.0f);
	glRotatef(180.0f,0.0f,1.0f,0.0f);
	Chair->drawChair();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
		glTranslatef(-7.0f,1.0f,-7.0f);
		glScalef(1.0f,1.5f,1.0f);
		drawAlmirah();
	glPopMatrix();

	


}