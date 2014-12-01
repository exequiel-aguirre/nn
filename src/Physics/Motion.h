#ifndef MotionH
#define MotionH
#include "../DataStructure/Velocity.h"
#include "../DataStructure/Acceleration.h"


class Motion {  
  private:
    Position* position;
    Velocity* velocity;
    Acceleration* acceleration;
    
  public:
	Motion(Position* position, Velocity* velocity,Acceleration* acceleration){
        this->position=position;
        this->velocity=velocity;
        this->acceleration=acceleration;       
      }    

    virtual ~Motion(){}
    //t is in fact a delta t (t is for time)
    //newPosition=currentPosition + deltaPosition
   Point* getPosition(float t){        
        float x=position->getX() + (velocity->getX()*t) + (0.5f*acceleration->getX()*t*t);
        float y=position->getY() + (velocity->getY()*t) + (0.5f*acceleration->getY()*t*t);
        float z=position->getZ() + (velocity->getZ()*t)+ (0.5f*acceleration->getZ()*t*t);
        
        return new Point(x,y,z);
    }
    //t is in fact a delta t (t is for time)
    //newVelocity=currentVelocity + deltaVelocity
    Point* getVelocity(float t){        
        //update velocity
        float x=velocity->getX() + (acceleration->getX()*t);
        float y=velocity->getY() + (acceleration->getY()*t);
        float z=velocity->getZ() + (acceleration->getZ()*t);

        return new Point(x,y,z);   
    }  

};


#endif
