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
        Point l=position.getLinear();
        l=l + (velocity.getLinear()*t);

        //This is important
        //For angular position, we cannot just add the velocity increment(rotations do not conmute).
        Point o=position.getAngular();
        //build angular velocity transform
        Point wt=velocity.getAngular()*t;
        Matrix mwt=Matrix(1.0);
        mwt.rotate(wt.y,wt.z,wt.x);
        //build angular position(orientation) transform
        Matrix mo=Matrix(1.0);
        mo.rotate(o.y,o.z,o.x);
        //compose both transform and traduce back to Euler angles
        Matrix mno=mwt*mo;
        std::vector<float> yzx=mno.getEulerAngles();

        o=Point(yzx[2],yzx[0],yzx[1]);
        
        return Position(l.x,l.y,l.z,o.x,o.y,o.z);
    }
    //t is in fact a delta t (t is for time)
    //newVelocity=currentVelocity + deltaVelocity
    Velocity getVelocity(float t,Velocity velocity,Acceleration acceleration){
        //update velocity
        Point v=velocity.getLinear();
        v=v + (acceleration.getLinear() * t);

        Point w=velocity.getAngular();
        w=w+ (acceleration.getAngular() * t);

        return Velocity(v,w);
    }  

};


#endif
