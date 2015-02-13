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
    
    virtual void render(Position& position){}

    virtual ModelObject& getModelObject(){}

    virtual void add(IEffect* effect){}

};
#endif

