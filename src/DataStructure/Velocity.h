#ifndef VelocityH
#define VelocityH
#include "Position.h"
#include "Point.h"

class Velocity:public Position{

  public:
	Velocity():Position(){}
	Velocity(float x,float y,float z):Position(x,y,z){}  		
	Velocity(float x,float y,float z,float phi,float theta,float psi):Position(x,y,z,phi,theta,psi){}
    virtual ~Velocity(){}  

    
	//dot product
	float operator*(const Point &p){
		return (x * p.x)+(y * p.y)+(z * p.z);
	}

	Velocity operator*(const float f){
		return Velocity(f*x,f*y,f*z);
	}

	Velocity operator+(const Velocity &p){
		return Velocity(x+p.x,y+p.y,z+p.z);
	}
	Velocity operator-(const Velocity &p){
		return Velocity(x-p.x,y-p.y,z-p.z);
	}

	Velocity operator-(){
		return Velocity(-x,-y,-z);
	}
  
};

#endif
