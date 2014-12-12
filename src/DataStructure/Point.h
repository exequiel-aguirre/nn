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
};

#endif