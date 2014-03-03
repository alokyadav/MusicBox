#include "controlPoint.h"

controlPoint::controlPoint(){
      x = 0.0;
      y = 0.0;
      z = 0.0;
}

void controlPoint::draw(){
      glPushMatrix();
            glDisable (GL_LIGHTING);
            glColor3f(1.0,0.0,0.0);
            glTranslatef(x, y, z);
            glutSolidSphere(0.05, 20, 20); 
            glEnable(GL_LIGHTING); 
      glPopMatrix();
}

void controlPoint::setCoordinates(float newx, float newy, float newz){
      x = newx;
      y = newy;
      z = newz;
}

void controlPoint::setZCoordinate(float newz){
      z = newz;
}

void controlPoint::setYCoordinate(float newy){
      y = newy;
}

void controlPoint::setXCoordinate(float newx){
      x = newx;
}

float controlPoint::getXCoordinate(){
      return x;
}

float controlPoint::getYCoordinate(){
      return y;
}

float controlPoint::getZCoordinate(){
      return z;
}

