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

    virtual ~IMap(){}
    
    virtual Point get(float u,float v){}
    virtual Point getNormal(float u,float v){}

    virtual float getUFrom(){}
	virtual float getUTo(){}
	virtual float getVFrom(){}
	virtual float getVTo(){}

	virtual int getLats(){}
	virtual int getLongs(){}


};
#endif

