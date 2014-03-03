# include "frustum.h"

frustum::frustum(){
      facT[0]=1.0;
      facT[1]=0.0;
      facT[2]=0.0;

      facB[0]=0.0;
      facB[1]=1.0;
      facB[2]=0.0;

      facF[0]=0.0;
      facF[1]=0.0;
      facF[2]=1.0;

      facBA[0]=1.0;
      facBA[1]=1.0;
      facBA[2]=0.0;
      
      facL[0]=1.0;
      facL[1]=0.0;
      facL[2]=1.0;
      
      facR[0]=0.0;
      facR[1]=1.0;
      facR[2]=1.0;
      
}
void frustum::setBackfaceColor(float R,float G ,float B){
            facBA[0]=R;
            facBA[1]=G;
            facBA[2]=B;
}
void frustum::setBottomfaceColor(float R,float G ,float B){
            facB[0]=R;
            facB[1]=G;
            facB[2]=B;
}
void frustum::setTopfaceColor(float R,float G ,float B){
            facT[0]=R;
            facT[1]=G;
            facT[2]=B;
}
void frustum::setFrontfaceColor(float R,float G ,float B){
            facF[0]=R;
            facF[1]=G;
            facF[2]=B;
}
void frustum::setLeftfaceColor(float R,float G ,float B){
            facL[0]=R;
            facL[1]=G;
            facL[2]=B;
}
void frustum::setRightfaceColor(float R,float G ,float B){
            facR[0]=R;
            facR[1]=G;
            facR[2]=B;
}
void frustum::draw(){

      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, this->Ftexture);
      glBegin(GL_QUADS);                
            //Top
            glTexCoord2f(0.0, 0.0); ;     
            glVertex3f(-1.0f, 1.0f, -1.0f);
            glTexCoord2f(0.0, 1.0); 
            glVertex3f(1.0f, 1.0f, -1.0f);
            glTexCoord2f(1.0, 1.0); 
            glVertex3f(1.0f, 1.0f,  1.0f);
            glTexCoord2f(1.0, 0.0); 
            glVertex3f(-1.0f, 1.0f,  1.0f);
       
            // Bottom
            glTexCoord2f(0.0, 0.0);       
            glVertex3f(-2.0f, -1.0f, -2.0f);
            glTexCoord2f(0.0, 1.0); 
            glVertex3f(2.0f, -1.0f, -2.0f);
            glTexCoord2f(1.0, 1.0); 
            glVertex3f(2.0f, -1.0f,  2.0f);
            glTexCoord2f(1.0, 0.0); 
            glVertex3f(-2.0f, -1.0f,  2.0f);
       
            // Front
            glTexCoord2f(0.0, 0.0);      
            glVertex3f(-2.0f, -1.0f, -2.0f);
            glTexCoord2f(0.0, 1.0); 
            glVertex3f(2.0f, -1.0f, -2.0f);
            glTexCoord2f(1.0, 1.0); 
            glVertex3f(1.0f, 1.0f, -1.0f);
            glTexCoord2f(1.0, 0.0); 
            glVertex3f(-1.0f, 1.0f, -1.0f);
       
            // Back
            glTexCoord2f(0.0, 0.0);     
            glVertex3f(-2.0f, -1.0f,  2.0f);
            glTexCoord2f(0.0, 1.0); 
            glVertex3f(2.0f, -1.0f,  2.0f);
            glTexCoord2f(1.0, 1.0); 
            glVertex3f(1.0f, 1.0f,  1.0f);
            glTexCoord2f(1.0, 0.0); 
            glVertex3f(-1.0f, 1.0f,  1.0f);

            // Left
            glTexCoord2f(0.0, 0.0);       
            glVertex3f(-2.0f, -1.0f, -2.0f);
            glTexCoord2f(0.0, 1.0); 
            glVertex3f(-2.0f, -1.0f,  2.0f);
            glTexCoord2f(1.0, 1.0); 
            glVertex3f(-1.0f, 1.0f,  1.0f);
            glTexCoord2f(1.0, 0.0); 
            glVertex3f(-1.0f, 1.0f, -1.0f);

            // Right
            glTexCoord2f(0.0, 0.0); 
            glVertex3f(2.0f, -1.0f, -2.0f);
            glTexCoord2f(0.0, 1.0); 
            glVertex3f(2.0f, -1.0f,  2.0f);
            glTexCoord2f(1.0, 1.0); 
            glVertex3f(1.0f, 1.0f,  1.0f);
            glTexCoord2f(1.0, 0.0); 
            glVertex3f(1.0f, 1.0f, -1.0f);
            
      glEnd();glDisable(GL_TEXTURE_2D);
      glDisable(GL_TEXTURE_2D);

}
void frustum::setTexture(GLuint tex){

      this->Ftexture=tex;
}