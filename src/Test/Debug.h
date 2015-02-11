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
    //to be called from the onAfterRender() (because this are positioned vertices )
    void renderEnclosingBox(){
        Point boundaryMin= boundary.getEnclosingBox().getDiagonalMin();
        Point boundaryMax= boundary.getEnclosingBox().getDiagonalMax();
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

    //to be called from the onRender() (because this are NOT positioned vertices )
    void renderReducedPolygon(){
        vector<Point> vertices=boundary.getReducedPolygon().getVertices();
        vector<Point>::iterator it;
        glBegin(GL_TRIANGLES);
        for(it=vertices.begin();it!=vertices.end();it+=3){      
              Point v1=(*it);
              Point v2=(*(it+1));
              Point v3=(*(it+2));
              Point n=((v2-v1)^(v3-v1)).normalize();
              glNormal3f(n.x,n.y,n.z);
              glVertex3f(v1.x,v1.y,v1.z);
              glVertex3f(v2.x,v2.y,v2.z);

              //glVertex3f(v2.x,v2.y,v2.z);
              glVertex3f(v3.x,v3.y,v3.z);

              //glVertex3f(v3.x,v3.y,v3.z);
              //glVertex3f(v1.x,v1.y,v1.z);
        }
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

    void renderNormals(){
        vector<vector<Point>> positionedTriangles=boundary.getReducedPolygon().getPositionedTriangles();
        vector<vector<Point>>::iterator it;
        glBegin(GL_LINES);
        for(it=positionedTriangles.begin();it!=positionedTriangles.end();it++){
              Point v1=(*it)[0];
              Point n=(*it)[3];
              glVertex3f(v1.x,v1.y,v1.z);
              glVertex3f(v1.x+n.x,v1.y+n.y,v1.z+n.z);
        }
        glEnd();
    }

    //to be called from the onAfterRender() (because this are positioned vertices )
    void renderMotionRay(){
      glBegin(GL_LINES);
        Point c0=boundary.getReducedPolygon().getPositionPoint();
        Point v=boundary.getReducedPolygon().getMotionRay();
        glVertex3f(c0.x,c0.y,c0.z);
        glVertex3f(c0.x+v.x, c0.y+v.y, c0.z+v.z);
      glEnd();
    }

    //to be called from the onAfterRender() (because this are positioned vertices )
    void renderPositionedTriangles(){
       vector<vector<Point>> positionedTriangles=boundary.getReducedPolygon().getPositionedTriangles();
        vector<vector<Point>>::iterator it;
        glBegin(GL_TRIANGLES);
        for(it=positionedTriangles.begin();it!=positionedTriangles.end();it++){
              Point v1=(*it)[0];
              Point v2=(*it)[1];
              Point v3=(*it)[2];
              Point n=(*it)[3];
              glNormal3f(n.x,n.y,n.z);
              glVertex3f(v1.x,v1.y,v1.z);
              glVertex3f(v2.x,v2.y,v2.z);

              //glVertex3f(v2.x,v2.y,v2.z);
              glVertex3f(v3.x,v3.y,v3.z);

              //glVertex3f(v3.x,v3.y,v3.z);
              //glVertex3f(v1.x,v1.y,v1.z);
        }
        glEnd();
    }
};
#endif
