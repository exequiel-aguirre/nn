#ifndef AccelerationH
#define AccelerationH
#include "Position.h"

class Acceleration:public Position{
   
  public:
	Acceleration():Position(){}
	Acceleration(float x,float y,float z):Position(x,y,z){}
	Acceleration(float x,float y,float z,float phi,float theta,float psi):Position(x,y,z,phi,theta,psi){}
    
    virtual ~Acceleration(){}    
};

#endif
