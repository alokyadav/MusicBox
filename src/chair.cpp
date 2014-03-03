# include "chair.h"


chair::chair(){
	quad= gluNewQuadric();
	support=new cuboid;
	image_tex=new imageLoader();
	chairParts.resize(4);
}
void chair::init(){
	Texture=image_tex->loadBMP_custom("./textures/top.bmp");
	Texture2=image_tex->loadBMP_custom("./textures/Chairtop.bmp");
	support->setTexture(Texture2);
	drawLegSupport();
	drawSupport();
	drawLeg();
	drawTop();

}
void chair::drawChair(){
	glPushMatrix();	
	glCallList(chairParts[0]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.75f,-1.4f,-.1f);
	glRotatef(6.0f,0.0f,1.0f,0.0f);
	glTranslatef(0.0f,0.0f,1.7f);
	glCallList(chairParts[1]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.75f,-1.4f,-0.1f);
	glRotatef(-6.0f,0.0f,1.0f,0.0f);
	glTranslatef(0.0f,0.0f,1.7f);
	glCallList(chairParts[1]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.75f,0.6f,-0.1f);
	glRotatef(6.0f,0.0f,1.0f,0.0f);
	glTranslatef(0.0f,0.0f,-1.7f);
	glScalef(1.0f,3.0f,1.0f);
	glCallList(chairParts[1]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.75f,0.6f,-0.1f);
	glRotatef(-6.0f,0.0f,1.0f,0.0f);
	glTranslatef(0.0f,0.0f,-1.7f);
	glScalef(1.0f,3.0f,1.0f);
	glCallList(chairParts[1]);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0f,2.2f,-1.8f);
		glRotatef(90.0f,1.0f,0.0f,0.0f);
		glCallList(chairParts[2]);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.75f,-1.5f,-0.1f);
		glRotatef(6.0f,0.0f,1.0f,0.0f);
		glCallList(chairParts[3]);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.75f,-1.5f,-0.1f);
		glRotatef(-6.0f,0.0f,1.0f,0.0f);
		glCallList(chairParts[3]);
	glPopMatrix();
}
void chair::drawTop(){
	chairParts[0] = glGenLists(1);
    glNewList(chairParts[0], GL_COMPILE);
	glPushMatrix();
	glScalef(2.0f,.1f,2.0f);
	drawShape();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f,-.2f,0.0f);
	glPushMatrix();
	glTranslatef(-1.75f,0.0f,-0.1f);
	glRotatef(-6.0f,0.0f,1.0f,0.0f);
	glScalef(.2f,.2f,1.9f);
	drawShape();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.75f,0.0f,-0.1f);
	glRotatef(6.0f,0.0f,1.0f,0.0f);
	glScalef(.2f,.2f,1.9f);
	drawShape();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f,0.0f,1.7f);
	glScalef(1.75f,.2f,.1f);
	drawShape();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-1.9f);

	//glRotatef(10.0f,0.0f,1.0f,0.0f);
	glScalef(1.4f,.2f,.1f);
	
	support->draw();
	glPopMatrix();
	glPopMatrix();
	glEndList();	
}
void chair::drawLegSupport(){

	chairParts[3] = glGenLists(1);
    glNewList(chairParts[3], GL_COMPILE);
    glTranslatef(0.0f,0.0f,-1.9f);
	drawRod(.15,3.8);
	glEndList();

}

void chair::drawLeg(){

	//glPushMatrix();
	chairParts[1] = glGenLists(1);
    glNewList(chairParts[1], GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->Texture2);
	glScalef(.2f,1.0f,.2f);
	drawShape();
	glDisable(GL_TEXTURE_2D);
	glEndList();
	//glPopMatrix();
}
void chair::drawSupport(){
	chairParts[2] = glGenLists(1);
    glNewList(chairParts[2], GL_COMPILE);
	glPushMatrix();
		glTranslatef(0.0f,0.0f,-.8f);
		glScalef(1.75f,.1f,.25f);
		support->draw();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0f,0.0f,.8f);
		glScalef(1.75f,.1f,.25f);
		support->draw();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-.8f,0.0f,-.8f);
		drawRod(.05f,1.6f);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(.8f,0.0f,-.8f);
		drawRod(.05f,1.6f);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0f,0.0f,-.8f);
		drawRod(.05f,1.6f);
	glPopMatrix();
	glEndList();
}
void chair::drawRod(float radius,float height){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->Texture2);
   	gluQuadricDrawStyle(quad, GLU_FILL);
   	gluQuadricTexture(quad,1);
   //glRotatef(90.0f,1.0f,0.0f,0.0f);
   //glColor3f(1.0f,0.0f,0.0f);
   	gluCylinder(quad,radius,radius,height,32,32);
   	glDisable(GL_TEXTURE_2D);


}
void chair::drawShape(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->Texture2);
	glColor3f(1.0f,0.0f,1.0f);
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);     // Green
    glVertex3f( 1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0, 1.0);
    glVertex3f(-1.25f, 1.0f,  1.0f);
	glTexCoord2f(1.0, 0.0);
    glVertex3f( 1.25f, 1.0f,  1.0f);
 
      // Bottom face (y = -1.0f)
     glNormal3f( 0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);     // Orange
    glVertex3f( 1.25f, -1.0f,  1.0f);
	glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.25f, -1.0f,  1.0f);
	glTexCoord2f(1.0, 1.0);
    glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0, 0.0);
    glVertex3f( 1.0f, -1.0f, -1.0f);
 
      // Front face  (z = 1.0f)
     glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0, 0.0);     // Red
    glVertex3f( 1.25f,  1.0f, 1.0f);
	glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.25f,  1.0f, 1.0f);
	glTexCoord2f(1.0, 1.0);
    glVertex3f(-1.25f, -1.0f, 1.0f);
	glTexCoord2f(1.0, 0.0);
    glVertex3f( 1.25f, -1.0f, 1.0f);
 
      // Back face (z = -1.0f)
     glNormal3f( 0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0, 0.0);     // Yellow
    glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0, 1.0);
    glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(1.0, 0.0);
    glVertex3f( 1.0f,  1.0f, -1.0f);
 
    // Left face (x = -1.0f)
    // Blue
     glNormal3f( -1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);      
	glVertex3f(-1.25f,  1.0f,  1.0f);
	glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(1.0, 1.0);
    glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0, 0.0);
    glVertex3f(-1.25f, -1.0f,  1.0f);
 
      // Right face (x = 1.0f)
    // Magenta
     glNormal3f( 1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);      
	glVertex3f(1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
    glVertex3f(1.25f,  1.0f,  1.0f);
	glTexCoord2f(1.0, 1.0);
    glVertex3f(1.25f, -1.0f,  1.0f);
	glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();
  glDisable(GL_TEXTURE_2D);
}