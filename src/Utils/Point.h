#ifndef PointH
#define PointH

class Point{
  
  private:
   float x;//put it in one line
   float y;
   float z;
  public:
	
	Point(float x,float y,float z){
		this->x=x;
		this->y=y;
		this->z=z;
	}
	Point(){}
	//virtual ~Point(){} do not use virtual because it messes up the glvertexbuff

	float &operator[](int i){
		if(i==0) return x;
		if(i==1) return y;
		if(i==2) return z;
	}
};

#endif