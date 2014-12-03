#ifndef CollisionDetectorH
#define CollisionDetectorH
#include "../Component/Component.h"
#include <typeinfo>


class CollisionDetector{
  private:    
    //TODO:this is component's property
    static const float e=0.88f;//Coefficient of restitution,1 is perfectly elastic,0 is perfectly plastic
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
            //TODO:same thing for x,y and z. Put all these in a method
            //elasctic collision on X           
            float v1,v2;
            float m1=c1->getMass();
            float m2=c2->getMass();
            float v1_i=c1->getVelocity()->getX();
            float v2_i=c2->getVelocity()->getX();            
            v1=((m1*v1_i) + (m2*v2_i) + (m2 * e *(v2_i-v1_i)))/(m1+m2);
            v2=((m1*v1_i) + (m2*v2_i) + (m1 * e *(v1_i-v2_i)))/(m1+m2);
            //if the velocity change sign, we set acceleration to 0(TODO:check if this is a correct aplication of the third law)
            //The if is to detect if the collision was on the X axis. left || right
            if((min1->x <= (max2->x-min2->x)) || (max1->x >= (max2->x-min2->x))) c1->getAcceleration()->setX(0.0f);
            if((min2->x <= (max1->x-min1->x)) || (max2->x >= (max1->x-min1->x))) c2->getAcceleration()->setX(0.0f);
            c1->getVelocity()->setX(v1);
            c2->getVelocity()->setX(v2);

            //elasctic collision on Y
            v1_i=c1->getVelocity()->getY();
            v2_i=c2->getVelocity()->getY();            
            v1=((m1*v1_i) + (m2*v2_i) + (m2 * e *(v2_i-v1_i)))/(m1+m2);
            v2=((m1*v1_i) + (m2*v2_i) + (m1 * e *(v1_i-v2_i)))/(m1+m2);
            //if the velocity change sign, we set acceleration to 0(TODO:check if this is a correct aplication of the third law)
            if((min1->y <= (max2->y-min2->y)) || (max1->y >= (max2->y-min2->y))) c1->getAcceleration()->setY(0.0f);
            if((min2->y <= (max1->y-min1->y)) || (max2->y >= (max1->y-min1->y))) c2->getAcceleration()->setY(0.0f);                
            c1->getVelocity()->setY(v1);
            c2->getVelocity()->setY(v2);

            //elasctic collision on Z
            v1_i=c1->getVelocity()->getZ();
            v2_i=c2->getVelocity()->getZ();            
            v1=((m1*v1_i) + (m2*v2_i) + (m2 * e *(v2_i-v1_i)))/(m1+m2);
            v2=((m1*v1_i) + (m2*v2_i) + (m1 * e *(v1_i-v2_i)))/(m1+m2);
            //if the velocity change sign, we set acceleration to 0(TODO:check if this is a correct aplication of the third law)
            if((min1->z <= (max2->z-min2->z)) || (max1->z >= (max2->z-min2->z))) c1->getAcceleration()->setZ(0.0f);
            if((min2->z <= (max1->z-min1->z)) || (max2->z >= (max1->z-min1->z))) c2->getAcceleration()->setZ(0.0f);
            c1->getVelocity()->setZ(v1);
            c2->getVelocity()->setZ(v2);
            
            /*
            
            std::string str(typeid(*c2).name());
            if(typeid(*c1)==typeid(*c2) && (str=="6Sphere")){
                std::cout << typeid(*c1).name()<<" collided with a "<< typeid(*c2).name()<<'\n';
                std::cout << v1 <<"," <<v2<<"\n";
            }

            */
            c1->setCollided(true);
            c2->setCollided(true);
            return true;
    	}else{
            return false;
        }
    }

};
#endif
