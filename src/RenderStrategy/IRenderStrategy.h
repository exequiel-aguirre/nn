#ifndef IRenderStrategyH
#define IRenderStrategyH

#include "../DataStructure/Position.h"
#include "../DataStructure/ModelObject.h"
/**
*
*/

class IRenderStrategy{

  public:
	IRenderStrategy(){}		

    virtual ~IRenderStrategy(){}
    
    virtual void render(Position& position,ModelObject& modelObject){}

    virtual ModelObject& initModelObject(ModelObject& modelObject,char* textureFilename){}

    virtual void add(IEffect* effect){}

};
#endif

