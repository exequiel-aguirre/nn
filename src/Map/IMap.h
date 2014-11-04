#ifndef IMapH
#define IMapH

/**
*This represent a map f:R^2->R^3
*/

class IMap{  
  public:
	IMap(){}		

    virtual ~IMap(){}
    
    float virtual getX(float u,float v){}
    float virtual getY(float u,float v){}
    float virtual getZ(float u,float v){}

//	EXE-TODO:add virtual!!!
    float virtual getUFrom(){}
	float virtual getUTo(){}
	float virtual getVFrom(){}
	float virtual getVTo(){}


};
#endif

