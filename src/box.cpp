#include "box.h"

using namespace std;

box::box(){
	theta = 0.0;
	height = -0.9;
	x = 0.0;
	y = 0.0;
	z = 0.0;
    image_box=new imageLoader();
	cube= new cuboid();

}


float box::getTheta(){
	return theta;
}
float box::getHeight(){
	return height;
}
void box::setHeight(float h){
	height=h;
}
void box::setTheta(float theta1){
	theta = theta1;
}

void box::drawBox(){
    glCallList (boxBody);
    glPushMatrix();
    drawPlatform();
    glPopMatrix();
    glPushMatrix();
    drawLid();
    glPopMatrix();
}

void box::drawPlatform(){
	//cout<<height<<endl;
    
  	glTranslatef(0.0f, height, 0.0f);
    glCallList (platform);
    
}

void box::drawLid(){


    //glColor3f(1.0,1.0,1.0);
  
    glTranslatef(0.0f, 1.0f, -1.0f);
    glRotatef(theta, 1.0f, 0.0f, 0.0f);
    glCallList (boxLid);

  

}
void box::glListDef(){
    this->texName = image_box->loadBMP_custom("./textures/boxSide.bmp");
    boxBody = glGenLists (1);
    glNewList (boxBody, GL_COMPILE); 
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->texName);
    glBegin(GL_QUADS); //Begin drawing quad faces    

        //Front
    glTexCoord2f(0.0, 0.0);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        //Back
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(1.0f, 1.0f, -1.0f);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        
        // Left face (x = -1.0f)
        glTexCoord2f(0.0, 0.0);    // Blue
        glVertex3f(-1.0f,  1.0f,  1.0f);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1.0f,  1.0f, -1.0f);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-1.0f, -1.0f,  1.0f);
 
        // Right face (x = 1.0f)
        glTexCoord2f(0.0, 0.0);     // Magenta
        glVertex3f(1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(1.0f,  1.0f,  1.0f);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.0f, -1.0f, -1.0f);  
    
    glEnd(); //End triangle coordinates
    glDisable(GL_TEXTURE_2D);
    glEndList ();

	boxLid = glGenLists (1);
	glNewList (boxLid, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->texName);


    glBegin(GL_QUADS); //Begin triangle coordinates
        glTexCoord2f(0.0, 0.0); 
        glVertex3f( 1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0, 1.0); 
        glVertex3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0, 1.0);       
        glVertex3f(-1.0f, 0.0f,  2.0f);
        glTexCoord2f(1.0, 0.0); 
        glVertex3f( 1.0f, 0.0f,  2.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glEndList ();
    
    platform = glGenLists (1);
    glNewList (platform, GL_COMPILE);
        glScalef(.9f,0.02f,0.8f);
        cube->setTexture(texName);
        cube->draw();
    glEndList ();

}
