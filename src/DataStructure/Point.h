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

	  //std::ostream::operator<< overload for Foo:
    friend std::ostream& operator<<(std::ostream& os , const Point* p)
    {
        os << "("<<p->x<<","<< p->y<<","<< p->z<<")"<< "\n";
    }
};

#endif