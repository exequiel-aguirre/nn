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
        //we make the enclosing box bigger, to avoid interpenetreting.TODO:avoid this
        Point min1=b1.getEnclosingBox().getDiagonalMin()-(EPSILON * Point(1,1,1));
        Point max1=b1.getEnclosingBox().getDiagonalMax()+(EPSILON * Point(1,1,1));
        Point min2=b2.getEnclosingBox().getDiagonalMin()-(EPSILON * Point(1,1,1));
        Point max2=b2.getEnclosingBox().getDiagonalMax()+(EPSILON * Point(1,1,1));
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

        //there's no reducedPolygon implemented( for loaded models)
        //TODO:implement it.
        if(vertices.empty() || triangles.empty()){
            b1.getCollisionStatus().setImpactNormal(-Point(0,1.0,0)).setDistance(0);
            b2.getCollisionStatus().setImpactNormal(Point(0,1.0,0)).setDistance(0);
            return 0;
        }

        float d=1000000;
        Point rv=pv-tv;//relative velocity. (so we can think of the triangle as not moving)
        float srv=rv.norm();
        for(itp=vertices.begin();itp!=vertices.end();itp++){
            //a point of c1
            Point& p=*itp;
            for(itt=triangles.begin();itt!=triangles.end();itt++){
                vector<Point>& triangle=(*itt);
                //check if the (moving) point is going to intersect this triangle
                if(srv>0.0 && !willIntersect(p,triangle,rv)) continue;
                //get the distance from p to the plane of the triangle of c2
                Point& x0=triangle[0];
                Point& n=triangle[3];
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
    bool pointInTriangle(Point& p,Point& a,Point& b,Point& c){
        return sameSide(p,a,b,c) && sameSide(p,b,a,c) && sameSide(p,c,a,b);
    }
    bool sameSide(Point& p1,Point& p2,Point& a,Point& b){
        Point cp1=(b-a)^(p1-a);
        Point cp2=(b-a)^(p2-a);
        return ((cp1 * cp2) >= 0);
    }


};
#endif
