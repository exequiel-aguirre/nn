#ifndef IMapH
#define IMapH
#include "../Utils/Point.h"

/**
*This represent a map f:R^2->R^3
*/

class IMap{  
  public:
	IMap(){}		

    virtual ~IMap(){}
    
    virtual Point* get(float u,float v){}


    virtual float getUFrom(){}
	virtual float getUTo(){}
	virtual float getVFrom(){}
	virtual float getVTo(){}


};
#endif

