#include "table.h"

table::table(){

   quad= gluNewQuadric();
   cube = new cuboid();
   hood=new frustum();
   image_tex=new imageLoader();
   tableParts.resize(2);

}
void table::init(){
   Texture=image_tex->loadBMP_custom("./textures/boxSide.bmp");
   gluQuadricDrawStyle(quad, GLU_FILL);
   gluQuadricTexture(quad,1);
   drawtableTop();
   createLeg();
}

void table::drawTable(){
   glPushMatrix();
   glCallList(tableParts[0]);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(5.0f,-1.75f,0.0f);
   glCallList(tableParts[1]);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(-5.0f,-1.75f,0.0f);
   glRotatef(180.0f,0.0f,1.0f,0.0f);
   glCallList(tableParts[1]);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(0.0f,-1.75f,5.0f);
   glRotatef(-90.0f,0.0f,1.0f,0.0f);
   glCallList(tableParts[1]);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(0.0f,-1.75f,-5.0f);
   glRotatef(90.0f,0.0f,1.0f,0.0f);
   glCallList(tableParts[1]);
   glPopMatrix();
}
void table::drawtableTop(){
   tableParts[0] = glGenLists(1);
   glNewList(tableParts[0], GL_COMPILE);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, this->Texture);
   glRotatef(90.0f,1.0f,0.0f,0.0f);
   glPushMatrix();
   gluQuadricOrientation(quad,GLU_INSIDE);
   gluDisk(quad, 0.0, 6.0f, 100, 15);
   gluQuadricOrientation(quad,GLU_OUTSIDE);
   gluCylinder(quad,6.0f,6.0f,.25f,100,32);
   glPushMatrix();
   gluQuadricOrientation(quad,GLU_OUTSIDE);
   glTranslatef(0.0f,0.0f,.25f);
   gluDisk(quad, 0.0, 6.0f, 100, 15);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(0.0f,0.0f,.25f);
   gluCylinder(quad,4.5f,4.5f,.5f,100,32);
   gluQuadricOrientation(quad,GLU_INSIDE);
   gluCylinder(quad,3.5f,3.5f,.5f,100,32);
   glPushMatrix();
   glTranslatef(0.0f,0.0f,.5f);
   gluQuadricOrientation(quad,GLU_OUTSIDE);
   gluDisk(quad, 3.5f, 4.5f, 100, 15);
   glPopMatrix();
   glPopMatrix();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
   glEndList();
}

void table::createLeg(){
      tableParts[1] = glGenLists(1);
      glNewList(tableParts[1], GL_COMPILE);
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, this->Texture);
      glPushMatrix();
      glScalef(1.0f,1.0f,.5f);
	   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out

		//glTexCoord2f(0.0, 0.0); 
      glNormal3f( 0.0f, 1.0f, 0.0f);
      glVertex3f( -1.5f, 1.0f, -1.0f);
		glTexCoord2f(0.0, 1.0);
      glVertex3f(-0.5f, 1.0f, -1.0f);
		glTexCoord2f(1.0, 1.0);
      glVertex3f(-0.5f, 1.0f,  1.0f);
		glTexCoord2f(1.0, 0.0);
      glVertex3f( -1.5f, 1.0f,  1.0f);
 
      // Bottom face (y = -1.0f)
      glNormal3f( 0.0f, -1.0f, 0.0f);
	  glTexCoord2f(0.0, 0.0);     // Orange
      glVertex3f( 1.5f, -1.0f,  1.0f);
		glTexCoord2f(0.0, 1.0);
      glVertex3f(.5f, -1.0f,  1.0f);
		glTexCoord2f(1.0, 1.0);
      	glVertex3f(.5f, -1.0f, -1.0f);
		glTexCoord2f(1.0, 0.0);
      	glVertex3f( 1.5f, -1.0f, -1.0f);
 
      // Front face  (z = 1.0f)
      glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0, 0.0);     // Red
      	glVertex3f( -0.5f,  1.0f, 1.0f);
		glTexCoord2f(0.0, 1.0);
      	glVertex3f(-1.5f,  1.0f, 1.0f);
		glTexCoord2f(1.0, 1.0);
      	glVertex3f(0.5f, -1.0f, 1.0f);
		glTexCoord2f(1.0, 0.0);
      	glVertex3f( 1.5f, -1.0f, 1.0f);
 
      // Back face (z = -1.0f)
      glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0, 0.0);     // Yellow
      glVertex3f( 1.5f, -1.0f, -1.0f);
		glTexCoord2f(0.0, 1.0);
      glVertex3f(0.5f, -1.0f, -1.0f);
		glTexCoord2f(1.0, 1.0);
      glVertex3f(-1.5f,  1.0f, -1.0f);
		glTexCoord2f(1.0, 0.0);
      glVertex3f( -.5f,  1.0f, -1.0f);
 
      // Left face (x = -1.0f)
     // Blue
      glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);      
		glVertex3f(-1.5f,  1.0f,  1.0f);
		glTexCoord2f(0.0, 1.0);
      glVertex3f(-1.5f,  1.0f, -1.0f);
		glTexCoord2f(1.0, 1.0);
     	glVertex3f(0.5f, -1.0f, -1.0f);
		glTexCoord2f(1.0, 0.0);
      	glVertex3f(0.5f, -1.0f,  1.0f);
 
      // Right face (x = 1.0f)
    // Magenta
   glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);      
		glVertex3f(-0.5f,  1.0f, -1.0f);
		glTexCoord2f(0.0, 1.0);
      	glVertex3f(-0.5f,  1.0f,  1.0f);
		glTexCoord2f(1.0, 1.0);
      	glVertex3f(1.5f, -1.0f,  1.0f);
		glTexCoord2f(1.0, 0.0);
      glVertex3f(1.5f, -1.0f, -1.0f);
   glEnd();
   
   glPopMatrix();
   glPushMatrix();
   glTranslatef(1.0f, -1.0f, 0.0f);
   gluQuadricTexture(quad,1);
   gluSphere(quad,0.707,20,20);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
   glPushMatrix();
      glTranslatef(1.0f,-1.5f,0.0f);
      glScalef(.4f,.6f,.4f);
      hood->draw();
   glPopMatrix();
   glEndList();


}


