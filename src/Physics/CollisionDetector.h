#ifndef CollisionDetectorH
#define CollisionDetectorH
#include "../Component/Component.h"
#include "../Utils/Utils.h"
#include <typeinfo>


class CollisionDetector{
  private:
    const float EPSILON=0.2f;
  public:
    CollisionDetector(){}
    virtual ~CollisionDetector(){}
    
    bool detect(Boundary* b1,Boundary* b2){

        Point* min1=b1->getEnclosingBox()->getDiagonalMin();
        Point* max1=b1->getEnclosingBox()->getDiagonalMax();
        Point* min2=b2->getEnclosingBox()->getDiagonalMin();
        Point* max2=b2->getEnclosingBox()->getDiagonalMax();
        //this is the intersection segment length (how bad the crash was...)
        float islx=std::min(max1->x,max2->x)-std::max(min1->x,min2->x);
        float isly=std::min(max1->y,max2->y)-std::max(min1->y,min2->y);
        float islz=std::min(max1->z,max2->z)-std::max(min1->z,min2->z);
       
        if( (islx >= 0) && (isly >= 0) && (islz >= 0) ) {
            
            if(getSeparation(b1,b2) > EPSILON) return false;

            b1->getCollisionStatus()->set(
                islx,
                isly,
                islz,
                min1->x <= min2->x,
                max1->x >= max2->x,
                min1->y <= min2->y,
                max1->y >= max2->y,
                min1->z <= min2->z,
                max1->z >= max2->z
                );
            b2->getCollisionStatus()->set(
                islx,
                isly,
                islz,
                min2->z <= min1->z,
                max2->z >= max1->z,
                min2->y <= min1->y,
                max2->y >= max1->y,
                min2->z <= min1->z,
                max2->z >= max1->z
                );

            return true;
    	}else{
            return false;
        }
    }

    //TODO:find a better name:We cannot call it distance, since separation(a,b)!=separation(b,a)
    float getSeparation(Boundary* b1,Boundary* b2){

        Point* p;
        vector<Point*>* vertices1=b1->getReducedPolygon()->getPositionedIndexedVertices();
        vector<Point*>::iterator it1;

        vector<std::pair<Point*,Point*>>* trianglePlanes2=b2->getReducedPolygon()->getPositionedTrianglePlanes();
        vector<std::pair<Point*,Point*>>::iterator it2;
        float d=1000000;
        for(it1=vertices1->begin();it1!=vertices1->end();it1++){
            //a point of c1
            p=*it1;
            for(it2=trianglePlanes2->begin();it2!=trianglePlanes2->end();it2++){
                //get the distance from p to the plane of each triangle of c2
                Point* x0=(*it2).first;
                Point* n=(*it2).second;
                float d1=distance(p,x0,n);
                if(d1<d) d=d1;
            }
        }

        return d;
    }

    float distance(Point* p,Point* x0,Point* n){
        //n.(p-x0)
        return fabs((n->x *(p->x-x0->x))+(n->y *(p->y-x0->y))+(n->z *(p->z-x0->z)));
    }
};
#endif
