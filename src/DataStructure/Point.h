#ifndef PointH
#define PointH

class Point{
  public:
   float x;//put it in one line
   float y;
   float z;
   
	Point(float x,float y,float z){
		this->x=x;
		this->y=y;
		this->z=z;
	}
	Point(){}
	//virtual ~Point(){} do not use virtual because it messes up the glvertexbuff	


	friend std::ostream& operator<<(std::ostream& os , const Point* p){
		os << "("<<p->x<<","<< p->y<<","<< p->z<<")"<< "\n";
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

	Point* rotate(float phi,float theta,float psi){
		if(phi==0 && theta==0 && psi==0) return this;
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

		return this;
	}
};

#endif