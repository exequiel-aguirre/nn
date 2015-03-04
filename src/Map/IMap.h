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
    
    virtual Point get(float u,float v)=0;
    virtual Point getNormal(float u,float v)=0;

  virtual float getUFrom()=0;
	virtual float getUTo()=0;
	virtual float getVFrom()=0;
	virtual float getVTo()=0;

	virtual int getLats()=0;
	virtual int getLongs()=0;


};
#endif

