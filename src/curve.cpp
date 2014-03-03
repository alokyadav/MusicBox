#include "curve.h"

curve::curve(){
      size = 0;
      sampling = 0.01;
}

void curve::addControlPoint(float pointx, float pointy, float pointz){
      ControlX.push_back(pointx);
      ControlY.push_back(pointy);
      ControlZ.push_back(pointz);
      size++;      
      drawControlPoints();
}

void curve::draw(){
      drawControlPoints();
      if(size > 1){
            CurveX.resize(0);
            CurveY.resize(0);
            CurveZ.resize(0);
            bezier_curve(ControlX, ControlY, ControlZ);
      }
      for(int i = 0; i < CurveX.size(); i++){
            glPushMatrix();
                  glDisable (GL_LIGHTING);
                  glColor3f(0.0,0.0,1.0);                
                  glTranslatef(CurveX[i], CurveY[i], CurveZ[i]);
                  glutSolidSphere(0.05, 20, 20);
                  glEnable(GL_LIGHTING);                                   
            glPopMatrix();
      }
}

vector<float> curve::getCurvePointsX(){
      if(CurveX.size() == 0 && size > 1){
            bezier_curve(ControlX, ControlY, ControlZ);
      }
      return CurveX;
}

vector<float> curve::getCurvePointsY(){
      if(CurveX.size() == 0 && size > 1){
            bezier_curve(ControlX, ControlY, ControlZ);
      }
      return CurveY;
}

vector<float> curve::getCurvePointsZ(){
      if(CurveX.size() == 0 && size > 1){
            bezier_curve(ControlX, ControlY, ControlZ);
      }
      return CurveZ;
}
void curve::drawControlPoints(){
      for(int i = 0; i < size; i++){
            glPushMatrix();
                  glDisable (GL_LIGHTING);
                  glColor3f(0.0,1.0,0.0);                
                  glTranslatef(ControlX[i], ControlY[i], ControlZ[i]);
                  glutSolidSphere(0.05, 20, 20);
                  glEnable(GL_LIGHTING);  
            glPopMatrix();
      }
}

vector<float> curve::computeCurveAtu(vector<float> pointx,vector<float> pointy,vector<float> pointz, int pointsSize, float u){
      vector<float> v(3);
      if(pointsSize == 1){
            v[0] = pointx[0];
            v[1] = pointy[0];
            v[2] = pointz[0];
      }
      else{
            vector<float> x1(pointsSize - 1);
            vector<float> y1(pointsSize - 1);
            vector<float> z1(pointsSize - 1);
            for(int i = 1; i < pointsSize; i++){
                  x1[i-1] = u*pointx[i] + (1-u)*pointx[i-1];
                  y1[i-1] = u*pointy[i] + (1-u)*pointy[i-1];
                  z1[i-1] = u*pointz[i] + (1-u)*pointz[i-1];
            }
            v = computeCurveAtu(x1, y1, z1, pointsSize - 1, u);
      }
      return v;
} 

void curve::setSampling(float newsampling){
      sampling = newsampling;
}

void curve::bezier_curve(vector<float> pointx, vector<float> pointy, vector<float> pointz){
      for(float u = 0; u <= 1; u += sampling){
            vector<float> v = computeCurveAtu(pointx, pointy, pointz, size, u);
            CurveX.push_back(v[0]);
            CurveY.push_back(v[1]);
            CurveZ.push_back(v[2]);
      }
}