#ifndef MotionH
#define MotionH
#include "../DataStructure/Velocity.h"
#include "../DataStructure/Acceleration.h"


class Motion {    
  public:
	Motion(){}

    virtual ~Motion(){}
    //t is in fact a delta t (t is for time)
    //newPosition=currentPosition + deltaPosition
   Position getPosition(float t,Position position,Velocity velocity,Acceleration acceleration){
        float x=position.getX() + (velocity.getX()*t) + (0.5f*acceleration.getX()*t*t);
        float y=position.getY() + (velocity.getY()*t) + (0.5f*acceleration.getY()*t*t);
        float z=position.getZ() + (velocity.getZ()*t)+ (0.5f*acceleration.getZ()*t*t);

        float phi=position.getPhi() + (velocity.getPhi()*t) + (0.5f*acceleration.getPhi()*t*t);
        float theta=position.getTheta() + (velocity.getTheta()*t) + (0.5f*acceleration.getTheta()*t*t);
        float psi=position.getPsi() + (velocity.getPsi()*t)+ (0.5f*acceleration.getPsi()*t*t);
        
        return Position(x,y,z,phi,theta,psi);
    }
    //t is in fact a delta t (t is for time)
    //newVelocity=currentVelocity + deltaVelocity
    Velocity getVelocity(float t,Velocity velocity,Acceleration acceleration){
        //update velocity
        float x=velocity.getX() + (acceleration.getX()*t);
        float y=velocity.getY() + (acceleration.getY()*t);
        float z=velocity.getZ() + (acceleration.getZ()*t);

        float phi=velocity.getPhi() + (acceleration.getPhi()*t);
        float theta=velocity.getTheta() + (acceleration.getTheta()*t);
        float psi=velocity.getPsi() + (acceleration.getPsi()*t);

        return Velocity(x,y,z,phi,theta,psi);
    }  

};


#endif
