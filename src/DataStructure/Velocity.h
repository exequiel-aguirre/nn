#ifndef VelocityH
#define VelocityH
#include "Position.h"

class Velocity:public Position{

  public:
	Velocity():Position(){}
	Velocity(float x,float y,float z):Position(x,y,z){}  		
	Velocity(float x,float y,float z,float phi,float theta,float psi):Position(x,y,z,phi,theta,psi){}
    virtual ~Velocity(){}  
  
};

#endif
