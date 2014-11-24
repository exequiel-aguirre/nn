#ifndef CollisionDetectorH
#define CollisionDetectorH
#include "../Component/Component.h"
#include "../Test/TimeBehavior.h"
#include "../Map/TimeMap.h"
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
            
            c1->setVelocity(-2.0f);
            c2->setVelocity(1.0f);
            //c1->move(0.0f,0.01f,0.0f);
            
            //std::cout << typeid(*c1).name()<<" collided with a "<< typeid(*c2).name()<<'\n';
          /*  std::cout << min1->x << "," << min1->y << "," << min1->z << '\n';
            std::cout << max1->x << "," << max1->y << "," << max1->z << '\n';
            std::cout << min2->x << "," << min2->y << "," << min2->z << '\n';
            std::cout << max2->x << "," << max2->y << "," << max2->z << '\n';*/
    	}        
    }

};
#endif
