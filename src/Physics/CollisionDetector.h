#ifndef CollisionDetectorH
#define CollisionDetectorH
#include "../DataStructure/Boundary.h"

class CollisionDetector{
  private:
    const float EPSILON=0.2f;
  public:
    CollisionDetector(){}
    virtual ~CollisionDetector(){}
    
    bool detect(Boundary& b1,Boundary& b2){

        Point min1=b1.getEnclosingBox().getDiagonalMin();
        Point max1=b1.getEnclosingBox().getDiagonalMax();
        Point min2=b2.getEnclosingBox().getDiagonalMin();
        Point max2=b2.getEnclosingBox().getDiagonalMax();
        //this is the intersection segment length (how bad the crash was...)
        float islx=std::min(max1.x,max2.x)-std::max(min1.x,min2.x);
        float isly=std::min(max1.y,max2.y)-std::max(min1.y,min2.y);
        float islz=std::min(max1.z,max2.z)-std::max(min1.z,min2.z);
       
        if( (islx >= 0) && (isly >= 0) && (islz >= 0) ) {
            
            if(getSeparation(b1,b2) > EPSILON) return false;

            b1.getCollisionStatus().set(
                islx,
                isly,
                islz,
                true
                );
            b2.getCollisionStatus().set(
                islx,
                isly,
                islz,
                true
                );

            return true;
    	}else{
            return false;
        }
    }

    //TODO:find a better name:We cannot call it distance, since separation(a,b)!=separation(b,a)
    float getSeparation(Boundary& b1,Boundary& b2){
        vector<Point> vertices;
        vector<std::pair<Point,Point>> trianglePlanes;
        vector<Point>::iterator itp;
        vector<std::pair<Point,Point>>::iterator ittp;
        //we use the reducedPolygon with more points for the vertices, and the normals of the other
        bool usingB2Normals=b1.getReducedPolygon().getPositionedIndexedVertices().size()>b2.getReducedPolygon().getPositionedIndexedVertices().size();
        if(usingB2Normals)
        {
            vertices=b1.getReducedPolygon().getPositionedIndexedVertices();
            trianglePlanes=b2.getReducedPolygon().getPositionedTrianglePlanes();
        }
        else
        {
            vertices=b2.getReducedPolygon().getPositionedIndexedVertices();
            trianglePlanes=b1.getReducedPolygon().getPositionedTrianglePlanes();
        }

        //there's no reducedPolygon implemented( for loaded models)
        //TODO:implement it.
        if(vertices.empty() || trianglePlanes.empty()){
            b1.getCollisionStatus().setImpactNormal(Point(0,1.0,0)).setDistance(0);
            b2.getCollisionStatus().setImpactNormal(-Point(0,1.0,0)).setDistance(0);
            return 0;
        }

        float d=1000000;
        for(itp=vertices.begin();itp!=vertices.end();itp++){
            //a point of c1
            Point& p=*itp;
            for(ittp=trianglePlanes.begin();ittp!=trianglePlanes.end();ittp++){
                //get the distance from p to the plane of each triangle of c2
                Point& x0=ittp->first;
                Point& n=ittp->second;
                float d1=fabs(n * (p-x0));
                if(d1<d){
                    d=d1;
                    if(d<EPSILON) b1.getCollisionStatus().setImpactPoint(p).setImpactNormal(usingB2Normals?n:-n).setDistance(d);
                    if(d<EPSILON) b2.getCollisionStatus().setImpactPoint(p).setImpactNormal(usingB2Normals?-n:n).setDistance(d);
                    if(d==0) return d;//if the distance is zero, no need to keep on going
                }
            }
        }

        return d;
    }


};
#endif
