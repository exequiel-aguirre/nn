#ifndef IMapH
#define IMapH

/**
*This represent a map f:R^2->R^3
*/

class IMap{  
  public:
	IMap(){}		

    virtual ~IMap(){}
    
    virtual float getX(float u,float v){}
    virtual float getY(float u,float v){}
    virtual float getZ(float u,float v){}


    virtual float getUFrom(){}
	virtual float getUTo(){}
	virtual float getVFrom(){}
	virtual float getVTo(){}


};
#endif

