#ifndef VelocityH
#define VelocityH
#include "Position.h"

class Velocity:public Position{

  public:
	Velocity():Position(){}
	Velocity(float x,float y,float z):Position(x,y,z){}
	Velocity(float x,float y,float z,float phi,float theta,float psi):Position(x,y,z,phi,theta,psi){}
	Velocity(Point v,Point w):Position(v.x,v.y,v.z,w.x,w.y,w.z){}
	Velocity(Point v):Position(v.x,v.y,v.z){}

    virtual ~Velocity(){}  

    
	//dot product
	float operator*(const Point &p){
		return (x * p.x)+(y * p.y)+(z * p.z);
	}

	Velocity operator*(const float rhs){
		return Velocity(x*rhs,y*rhs,z*rhs);
	}
	friend Velocity operator*(float lhs, Velocity rhs) {
		return rhs*lhs;
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
