#ifndef AnimationH
#define AnimationH

#include "Model.h"
#include "../RenderStrategy/AnimationStrategy.h"


class Animation: public Model {
  public:  	 
	Animation(Position&& position,char* modelFilename):Model(position,new AnimationStrategy(modelFilename,"img/human.bmp")){}

    virtual ~Animation(){}

};


#endif
