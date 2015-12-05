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
    void renderEnclosingBox(Point& boundaryMin,Point& boundaryMax){
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
      glBegin(GL_LINES);
        Point x0=boundary.getCollisionStatus().getImpactPoint();
        Point n=boundary.getCollisionStatus().getImpactNormal();
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
