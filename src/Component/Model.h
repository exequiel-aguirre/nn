#ifndef ModelH
#define ModelH

#include "Component.h"
#include "../RenderStrategy/TextureStrategy.h"



class Model: public Component {

  public:
  	 Model(Position* position,IRenderStrategy* renderStrategy):Component(position){
	  	this->renderStrategy=renderStrategy;
	  }
	  Model(Position* position,char* modelFilename):Model(position,new TextureStrategy(modelFilename,"img/human.bmp")){}	  

    virtual ~Model(){}

};


#endif
