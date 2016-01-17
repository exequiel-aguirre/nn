#ifndef DebugH
#define DebugH

#include "../DataStructure/Boundary.h"

class Debug{
	Boundary boundary;
  public:
    Debug(){}
    Debug(Boundary& boundary){
    	this->boundary=boundary;
    }
    void renderEnclosingBox(){
      renderEnclosingBox(boundary.getEnclosingBox().getDiagonalMin(),boundary.getEnclosingBox().getDiagonalMax());
    }
    //to be called from the onAfterRender() (because this are positioned vertices )
    void renderEnclosingBox(Point boundaryMin,Point boundaryMax){
        glLineWidth(3.0);
        glBegin(GL_LINES);

          //front rectangle
          glVertex3f(boundaryMin.x,boundaryMin.y,boundaryMin.z);
          glVertex3f(boundaryMax.x,boundaryMin.y,boundaryMin.z);

          glVertex3f(boundaryMax.x,boundaryMin.y,boundaryMin.z);
          glVertex3f(boundaryMax.x,boundaryMax.y,boundaryMin.z);

          glVertex3f(boundaryMax.x,boundaryMax.y,boundaryMin.z);
          glVertex3f(boundaryMin.x,boundaryMax.y,boundaryMin.z);

          glVertex3f(boundaryMin.x,boundaryMax.y,boundaryMin.z);
          glVertex3f(boundaryMin.x,boundaryMin.y,boundaryMin.z);


          //back rectangle
          glVertex3f(boundaryMin.x,boundaryMin.y,boundaryMax.z);
          glVertex3f(boundaryMax.x,boundaryMin.y,boundaryMax.z);

          glVertex3f(boundaryMax.x,boundaryMin.y,boundaryMax.z);
          glVertex3f(boundaryMax.x,boundaryMax.y,boundaryMax.z);

          glVertex3f(boundaryMax.x,boundaryMax.y,boundaryMax.z);
          glVertex3f(boundaryMin.x,boundaryMax.y,boundaryMax.z);

          glVertex3f(boundaryMin.x,boundaryMax.y,boundaryMax.z);
          glVertex3f(boundaryMin.x,boundaryMin.y,boundaryMax.z);

          //depth rectangle
          glVertex3f(boundaryMin.x,boundaryMin.y,boundaryMin.z);
          glVertex3f(boundaryMin.x,boundaryMin.y,boundaryMax.z);

          glVertex3f(boundaryMax.x,boundaryMin.y,boundaryMin.z);
          glVertex3f(boundaryMax.x,boundaryMin.y,boundaryMax.z);

          glVertex3f(boundaryMax.x,boundaryMax.y,boundaryMin.z);
          glVertex3f(boundaryMax.x,boundaryMax.y,boundaryMax.z);

          glVertex3f(boundaryMin.x,boundaryMax.y,boundaryMin.z);
          glVertex3f(boundaryMin.x,boundaryMax.y,boundaryMax.z);

          
        glEnd();
    }
    
    //to be called from the onAfterRender() (because this are positioned vertices )
    void renderImpactNormal(){
      glLineWidth(3.0);
      glBegin(GL_LINES);
        Point x0=boundary.getCollisionStatus().getImpactPoint();
        Point n=boundary.getCollisionStatus().getImpactNormal() * 3.0;
        glVertex3f(x0.x,x0.y,x0.z);
        glVertex3f(x0.x+n.x, x0.y+n.y, x0.z+n.z);
      glEnd();

    }

    void renderContactPoints(){
      glEnable(GL_PROGRAM_POINT_SIZE);
      glPointSize(14.0);
      vector<ContactPoint> points=boundary.getCollisionStatus().getContactPoints();
      glBegin(GL_POINTS);
        for(ContactPoint& cp:points){
          //glVertex3f(cp.position1.x,cp.position1.y,cp.position1.z);
          glVertex3f(cp.position2.x,cp.position2.y,cp.position2.z);
        }
      glEnd();
    }

    void renderImpactPoints(){
      glEnable(GL_PROGRAM_POINT_SIZE);
      //glPointSize(34.0);
      glLineWidth(13.0);
      vector<Point> points=boundary.getCollisionStatus().getImpactPoints();
      Point n=boundary.getCollisionStatus().getImpactNormal() *3.0;
      glBegin(GL_LINES);
        for(Point& p:points){
          glVertex3f(p.x,p.y,p.z);
          glVertex3f(p.x+n.x,p.y+n.y,p.z+n.z);
        }
      glEnd();
    }
    //to be called from the onAfterRender() (because this are positioned vertices )
    void renderMotionRay(){
      glLineWidth(3.0);
      glBegin(GL_LINES);
        Point x0=boundary.getEnclosingBox().getCenter();
        Point n=boundary.getReducedPolygon().getMotionRay() * 3.0;
        glVertex3f(x0.x,x0.y,x0.z);
        glVertex3f(x0.x+n.x, x0.y+n.y, x0.z+n.z);
      glEnd();

    }

    void renderLine( Point c0,Point v){
      glBegin(GL_LINES);
        glVertex3f(c0.x,c0.y,c0.z);
        glVertex3f(c0.x+v.x, c0.y+v.y, c0.z+v.z);
      glEnd();
    }

};
#endif
