#ifndef IRenderStrategyH
#define IRenderStrategyH

#include "../DataStructure/ModelObject.h"
/**
*
*/

class IRenderStrategy{

  public:
	IRenderStrategy(){}		

    virtual ~IRenderStrategy(){}
    
    virtual void render(){}

    virtual ModelObject* getModelObject(){}

};
#endif

