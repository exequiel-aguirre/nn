#ifndef CollisionDetectorH
#define CollisionDetectorH
#include "../DataStructure/Boundary.h"

class CollisionDetector{
  private:
    const float EPSILON=0.2f;
    const float DELTA=0.0000000001;
  public:
    CollisionDetector(){}
    virtual ~CollisionDetector(){}
    
    bool detect(Boundary& b1,Boundary& b2){

        Point& min1=b1.getEnclosingBox().getDiagonalMin();
        Point& max1=b1.getEnclosingBox().getDiagonalMax();
        Point& min2=b2.getEnclosingBox().getDiagonalMin();
        Point& max2=b2.getEnclosingBox().getDiagonalMax();
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
        Point pv;//point velocity
        vector<Point>::iterator itp;
        vector<vector<Point>> triangles;
        Point tv;//triangle velocity
        vector<vector<Point>>::iterator itt;
        //we use the reducedPolygon with more points for the vertices, and the normals of the other
        bool usingB2Normals=b1.getReducedPolygon().getPointDensity()>b2.getReducedPolygon().getPointDensity();
        if(usingB2Normals)
        {
            vertices=b1.getReducedPolygon().getPositionedIndexedVertices();
            pv=b1.getReducedPolygon().getMotionRay();
            triangles=b2.getReducedPolygon().getPositionedTriangles();
            tv=b2.getReducedPolygon().getMotionRay();
        }
        else
        {
            vertices=b2.getReducedPolygon().getPositionedIndexedVertices();
            pv=b2.getReducedPolygon().getMotionRay();
            triangles=b1.getReducedPolygon().getPositionedTriangles();
            tv=b1.getReducedPolygon().getMotionRay();
        }


        float d=1000000;
        Point rv=pv-tv;//relative velocity. (so we can think of the triangle as not moving)
        for(itp=vertices.begin();itp!=vertices.end();itp++){
            //a point of c1
            Point& p=*itp;
            for(itt=triangles.begin();itt!=triangles.end();itt++){
                vector<Point>& triangle=(*itt);
                Point& x0=triangle[0];
                Point& n=triangle[3];
                //check if the (moving towards) point is going to intersect this triangle
                if(fabs(n*rv)>DELTA && !willIntersect(p,triangle,rv)) continue;
                //get the distance from p to the plane of the triangle of c2
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

    bool willIntersect(Point& p,vector<Point>& triangle,Point& rv){
        Point& x0=triangle[0];
        Point& n=triangle[3];
        //get the intersection point
        float t=(n*(x0-p))/(n*rv);
        if(isnan(t) || t<0.0) return false;//TODO:check if t is nan just when (n*v)==0
        Point ip=p + t*rv;

        return pointInTriangle(ip,triangle[0],triangle[1],triangle[2]);
    }
    //We find the coordinates (u,v) for the point p, in the base {c-a,b-a}, so
    //p=a+ u (c-a) + v (b-a)
    bool pointInTriangle(Point& p,Point& a,Point& b,Point& c){
        Point v0=c-a;
        Point v1=b-a;
        Point v2=p-a;
        float u=((v1*v1)*(v2*v0)-(v1*v0)*(v2*v1))/((v0*v0)*(v1*v1)-(v0*v1)*(v1*v0));
        float v=((v0*v0)*(v2*v1)-(v0*v1)*(v2*v0))/((v0*v0)*(v1*v1)-(v0*v1)*(v1*v0));

        return (0<=u) && (0<=v) && (u+v<1);
    }


};
#endif
