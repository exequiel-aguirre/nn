#ifndef IRenderStrategyH
#define IRenderStrategyH

/**
*
*/

class IRenderStrategy{
  protected:
  	static const int MAX_STEP=500;
	int lats=24;
	int longs=24; 

  public:
	IRenderStrategy(){}		

    virtual ~IRenderStrategy(){}
    
    virtual void render(){}


};
#endif

