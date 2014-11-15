#ifndef AnimationH
#define AnimationH

#include "Model.h"
#include <GL/gl.h>
#include "../Utils/ModelObject.h"
#include "../RenderStrategy/AnimationStrategy.h"
#include <vector>
using std::vector;


class Animation: public Model {
  public:  	 
	Animation(Position* position,char* modelFilename):Model(position,new AnimationStrategy(modelFilename,"img/human.bmp")){}	  

    virtual ~Animation(){}

};


#endif
