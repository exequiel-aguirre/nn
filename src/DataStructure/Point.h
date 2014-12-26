#ifndef PointH
#define PointH
#include "RawPoint.h"

class Point{
  public:
   float x;//put it in one line
   float y;
   float z;
   //this is for the fastStrategy
   RawPoint rawPoint;

	Point(float x,float y,float z){
		this->x=x;
		this->y=y;
		this->z=z;
	}
	Point(){}


	void set(float x,float y,float z){
		this->x=x;
		this->y=y;
		this->z=z;
	}

	RawPoint getRawPoint(){
		rawPoint.x=this->x;
		rawPoint.y=this->y;
		rawPoint.z=this->z;
		return rawPoint;
	}

	friend std::ostream& operator<<(std::ostream& os , const Point p){
		os << "("<<p.x<<","<< p.y<<","<< p.z<<")"<< "\n";
	}

	bool operator==(const Point& p){
		return (x==p.x) && (y==p.y) && (z==p.z);
	}

	bool operator<(const Point& p) const{
		if(x!=p.x) return x<p.x;
		if(y!=p.y) return y<p.y;
		if(z!=p.z) return z<p.z;
		//they are equals
		return false;
	}

	Point rotate(float phi,float theta,float psi){
		if(phi==0 && theta==0 && psi==0) return *this;
		float xr,yr,zr;
		phi=phi*M_PI/180.0f;
		theta=theta*M_PI/180.0f;
		psi=psi*M_PI/180.0f;

		//rotation on z axis
		xr=(cos(psi)*x)-(sin(psi)*y);
		yr=(sin(psi)*x)+(cos(psi)*y);
		//z=z
		x=xr;
		y=yr;

		//rotation on y axis
		xr=(cos(theta)*x)+(sin(theta)*z);
		//y=y
		zr=(-sin(theta)*x)+(cos(theta)*z);
		x=xr;
		z=zr;

		//rotation on x axis
		//x=x;
		yr=(cos(phi)*y)-(sin(phi)*z);
		zr=(sin(phi)*y)+(cos(phi)*z);
		y=yr;
		z=zr;

		return *this;
	}
	Point translate(float x,float y,float z){
		this->x+=x;
		this->y+=y;
		this->z+=z;

		return *this;
	}

	//cross product
	Point operator^(const Point& p) {
		//y1 z2-z1 y2,z1 x2-x1 z2,x1 y2-y1 x2
		float x1=this->x;
		float y1=this->y;
		float z1=this->z;
		float x2=p.x;
		float y2=p.y;
		float z2=p.z;
		return Point((y1*z2)-(z1*y2),(z1*x2)-(x1*z2),(x1*y2)-(y1*x2));
	}

	//dot product
	float operator*(const Point &p){
		return (x * p.x)+(y * p.y)+(z * p.z);
	}

	Point operator+(const Point &p){
		return Point(x+p.x,y+p.y,z+p.z);
	}
	Point operator-(const Point &p){
		return Point(x-p.x,y-p.y,z-p.z);
	}

	Point operator-(){
		return Point(-x,-y,-z);
	}

	Point normalize(){
		float norm=sqrt((x*x) + (y*y) + (z*z));
		if(norm==0.0f) return *this;
		x=x/norm;
		y=y/norm;
		z=z/norm;
		return *this;
	}

	float norm(){
		return sqrt((x*x) + (y*y) + (z*z));
	}
};

#endif