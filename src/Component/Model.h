#ifndef ModelH
#define ModelH

#include "Component.h"
#include "../RenderStrategy/RenderStrategy.h"



class Model: public Component {

  public:
	Model(Position& position,IRenderStrategy* renderStrategy):Component(position,renderStrategy){}

	Model(Position&& position,IRenderStrategy* renderStrategy):Model(position,renderStrategy){}

	Model(Position&& position,char* modelFilename):Model(position,new RenderStrategy(modelFilename,"img/human.bmp",GL_TRIANGLES)){}

    virtual ~Model(){}

};


#endif
