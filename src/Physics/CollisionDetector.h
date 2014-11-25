#ifndef CollisionDetectorH
#define CollisionDetectorH
#include "../Component/Component.h"
#include <typeinfo>


class CollisionDetector{
  public:
    CollisionDetector(){}
    virtual ~CollisionDetector(){}
    
    static bool detect(Component* c1,Component* c2){
        if((c1->getBoundaryMin()==NULL)||(c1->getBoundaryMax()==NULL) ||
            (c2->getBoundaryMin()==NULL)||(c2->getBoundaryMax()==NULL)) return false;    	
    	
        Point* min1=c1->getBoundaryMin();
        Point* max1=c1->getBoundaryMax();
        Point* min2=c2->getBoundaryMin();
        Point* max2=c2->getBoundaryMax();
       
        if( (min1->x <= max2->x) && (max1->x >= min2->x) &&
            (min1->y <= max2->y) && (max1->y >= min2->y) &&
            (min1->z <= max2->z) && (max1->z >= min2->z)  ) {
            
            //elasctic collision on X           
            float v1,v2;
            float m1=c1->getMass();
            float m2=c2->getMass();
            float v1_i=c1->getVelocity()->getX();
            float v2_i=c2->getVelocity()->getX();            
            v1=((m1-m2)/(m1+m2)*v1_i) + (2* m2/(m1+m2) *v2_i);
            v2=((m2-m1)/(m1+m2)*v2_i) + (2* m1/(m1+m2) *v1_i);
            c1->getVelocity()->setX(v1);
            c2->getVelocity()->setX(v2);
            //elasctic collision on Y
            v1_i=c1->getVelocity()->getY();
            v2_i=c2->getVelocity()->getY();            
            v1=((m1-m2)/(m1+m2)*v1_i) + (2* m2/(m1+m2) *v2_i);
            v2=((m2-m1)/(m1+m2)*v2_i) + (2* m1/(m1+m2) *v1_i);
            c1->getVelocity()->setY(v1);
            c2->getVelocity()->setY(v2);

            //elasctic collision on Z
            v1_i=c1->getVelocity()->getZ();
            v2_i=c2->getVelocity()->getZ();            
            v1=((m1-m2)/(m1+m2)*v1_i) + (2* m2/(m1+m2) *v2_i);
            v2=((m2-m1)/(m1+m2)*v2_i) + (2* m1/(m1+m2) *v1_i);
            c1->getVelocity()->setZ(v1);
            c2->getVelocity()->setZ(v2);
            
            //c1->move(0.0f,0.01f,0.0f);
            //std::cout << typeid(*c1).name()<<" collided with a "<< typeid(*c2).name()<<'\n';
            //std::cout << v1 <<"," <<v2<<"\n";
            //std::cout << m1 <<"," <<m2<<"\n\n";
          /*  std::cout << min1->x << "," << min1->y << "," << min1->z << '\n';
            std::cout << max1->x << "," << max1->y << "," << max1->z << '\n';
            std::cout << min2->x << "," << min2->y << "," << min2->z << '\n';
            std::cout << max2->x << "," << max2->y << "," << max2->z << '\n';*/
    	}        
    }

};
#endif
