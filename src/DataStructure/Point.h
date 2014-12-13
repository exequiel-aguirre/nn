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

	Point* rotateCopy(float phi,float theta,float psi){
		if(phi==0 && theta==0 && psi==0) return new Point(x,y,z);
		float xa,ya,za;
		float xr=this->x;
		float yr=this->y;
		float zr=this->z;
		phi=phi*M_PI/180.0f;
		theta=theta*M_PI/180.0f;
		psi=psi*M_PI/180.0f;

		//rotation on z axis
		xa=(cos(psi)*xr)-(sin(psi)*yr);
		ya=(sin(psi)*xr)+(cos(psi)*yr);
		//z=z
		xr=xa;
		yr=ya;

		//rotation on y axis
		xa=(cos(theta)*xr)+(sin(theta)*zr);
		//y=y
		za=(-sin(theta)*xr)+(cos(theta)*zr);
		xr=xa;
		zr=za;

		//rotation on x axis
		//x=x;
		ya=(cos(phi)*yr)-(sin(phi)*zr);
		za=(sin(phi)*yr)+(cos(phi)*zr);
		yr=ya;
		zr=za;

		return new Point(xr,yr,zr);
	}
};

#endif