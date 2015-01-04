#ifndef DebugH
#define DebugH

#include "../DataStructure/Boundary.h"

class Debug{
	Boundary boundary;
  public:
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
        glBegin(GL_LINES);
        for(it=vertices.begin();it!=vertices.end();it+=3){      
              Point v1=(*it);
              Point v2=(*(it+1));
              Point v3=(*(it+2));
              Point n=((v2-v1)^(v3-v1)).normalize();
              glNormal3f(n.x,n.y,n.z);
              glVertex3f(v1.x,v1.y,v1.z);
              glVertex3f(v2.x,v2.y,v2.z);

              glVertex3f(v2.x,v2.y,v2.z);
              glVertex3f(v3.x,v3.y,v3.z);

              glVertex3f(v3.x,v3.y,v3.z);
              glVertex3f(v1.x,v1.y,v1.z);
        }
        glEnd();

        vector<std::pair<Point,Point>> trianglePlanes=boundary.getReducedPolygon().getTrianglePlanes();
        vector<std::pair<Point,Point>>::iterator itp;
        glBegin(GL_LINES);
        for(itp=trianglePlanes.begin();itp!=trianglePlanes.end();itp++){
            Point x0=(*itp).first;
            Point n=(*itp).second;
            glVertex3f(x0.x,x0.y,x0.z);
            glVertex3f(x0.x+n.x, x0.y+n.y, x0.z+n.z);
        }
        glEnd();
    }      

};
#endif
