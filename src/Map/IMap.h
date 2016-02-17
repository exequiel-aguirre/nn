#ifndef IMapH
#define IMapH
#include "../DataStructure/Point.h"

/**
*This represent a map f:R^2->R^3
*/

class IMap{
  protected:
    const float EPSILON=0.000001;
  public:

	IMap(){}

    
    virtual Point get(float u,float v)=0;
    virtual Point getNormal(float u,float v)=0;
    Point getTangent(float u,float v){
        float h=getVFrom()-getVTo();

        float deltaV=h/this->getLongs();
        Point t=(this->get(u,v+deltaV) - this->get(u,v))*(1/deltaV);

        return t.normalize();
    }

    virtual float getUFrom()=0;
	virtual float getUTo()=0;
	virtual float getVFrom()=0;
	virtual float getVTo()=0;

	virtual int getLats()=0;
	virtual int getLongs()=0;

    virtual std::function<Point(Point)> getSupportFunction(){
      return std::function<Point(Point)>();
    }


};
#endif

