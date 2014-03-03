# include "cuboid.h"

cuboid::cuboid(){
      facT[0]=0.0;
      facT[1]=0.0;
      facT[2]=1.0;

      facB[0]=1.0;
      facB[1]=1.0;
      facB[2]=0.0;

      facF[0]=1.0;
      facF[1]=0.0;
      facF[2]=0.0;

      facBA[0]=0.0;
      facBA[1]=1.0;
      facBA[2]=0.0;
      
      facL[0]=1.0;
      facL[1]=0.0;
      facL[2]=1.0;
      
      facR[0]=0.0;
      facR[1]=1.0;
      facR[2]=1.0;
}
void cuboid::setBackfaceColor(float R,float G ,float B){
		facBA[0]=R;
		facBA[1]=G;
		facBA[2]=B;
}
void cuboid::setBottomfaceColor(float R,float G ,float B){
		facB[0]=R;
		facB[1]=G;
		facB[2]=B;
}
void cuboid::setTopfaceColor(float R,float G ,float B){
		facT[0]=R;
		facT[1]=G;
		facT[2]=B;
}
void cuboid::setFrontfaceColor(float R,float G ,float B){
		facF[0]=R;
		facF[1]=G;
		facF[2]=B;
}
void cuboid::setLeftfaceColor(float R,float G ,float B){
		facL[0]=R;
		facL[1]=G;
		facL[2]=B;
}
void cuboid::setRightfaceColor(float R,float G ,float B){
		facR[0]=R;
		facR[1]=G;
		facR[2]=B;
}

void cuboid::setTexture(GLuint tex){

      this->Texture=tex;
}
void cuboid::draw(){
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, this->Texture);
	   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
            glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);     // Green
      glVertex3f( 1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0, 1.0);
      glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0, 1.0);
      glVertex3f(-1.0f, 1.0f,  1.0f);
		glTexCoord2f(1.0, 0.0);
      glVertex3f( 1.0f, 1.0f,  1.0f);
 
      // Bottom face (y = -1.0f)
      glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);     // Orange
      glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(0.0, 1.0);
      glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0, 1.0);
      glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0, 0.0);
      glVertex3f( 1.0f, -1.0f, -1.0f);
 
      // Front face  (z = 1.0f)
      glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0, 0.0);     // Red
      glVertex3f( 1.0f,  1.0f, 1.0f);
		glTexCoord2f(0.0, 1.0);
      glVertex3f(-1.0f,  1.0f, 1.0f);
		glTexCoord2f(1.0, 1.0);
      glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0, 0.0);
      glVertex3f( 1.0f, -1.0f, 1.0f);
 
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
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0, 1.0);
      glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(1.0, 1.0);
      glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0, 0.0);
      glVertex3f(-1.0f, -1.0f,  1.0f);
 
      // Right face (x = 1.0f)
    // Magenta
            glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);      
		glVertex3f(1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0, 1.0);
      glVertex3f(1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0, 1.0);
      glVertex3f(1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0, 0.0);
      glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();
   glDisable(GL_TEXTURE_2D);

}
