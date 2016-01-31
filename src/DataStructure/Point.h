#ifndef PointH
#define PointH
#include "RawPoint.h"
#include "Matrix.h"

class Point{
  public:
   float x;//put it in one line
   float y;
   float z;

   static constexpr float ZERO_EPSILON=6e-05;
	Point(float x,float y,float z){
		this->x=x;
		this->y=y;
		this->z=z;
	}
	Point():Point(0,0,0){}



	void set(float x,float y,float z){
		this->x=x;
		this->y=y;
		this->z=z;
	}
	//this is for the renderStrategy
	RawPoint getRawPoint(){
		RawPoint rawPoint;
		rawPoint.x=this->x;
		rawPoint.y=this->y;
		rawPoint.z=this->z;
		return rawPoint;
	}

	friend std::ostream& operator<<(std::ostream& os , const Point p){
		return os << "("<<p.x<<","<< p.y<<","<< p.z<<")"<< "\n";
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

	Point operator*(const float rhs){
		return Point(x*rhs,y*rhs,z*rhs);
	}

	//return matrix*Point(p.x,p.y,p.z,1)
	friend Point operator*(const Matrix& m,Point p){
		float x=m.rawMatrix[0]*p.x + m.rawMatrix[1]*p.y + m.rawMatrix[2]*p.z + m.rawMatrix[3];
		float y=m.rawMatrix[4]*p.x + m.rawMatrix[5]*p.y + m.rawMatrix[6]*p.z + m.rawMatrix[7];
		float z=m.rawMatrix[8]*p.x + m.rawMatrix[9]*p.y + m.rawMatrix[10]*p.z + m.rawMatrix[11];

		return Point(x,y,z);
	}

	friend Point operator*(float lhs, Point rhs) {
		return rhs*lhs;
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

	//rename to isCloseToZero(or something like that)
	bool isZero(){
		return isSmallerThan(ZERO_EPSILON);
	}
	bool isSmallerThan(float value){
		return (x<value && x>-value &&
				y<value && y>-value &&
				z<value && z>-value);
	}
};

#endif
