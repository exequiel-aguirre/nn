#ifndef ModelH
#define ModelH

#include "Component.h"
#include "../Utils/Utils.h"
#include "../DataStructure/ModelObject.h"



class Model: public Component {

  public:
	Model(Position& position,const char* modelFilename):Component(position,Utils::loadModel(modelFilename),"img/human.bmp",GL_TRIANGLES){}
	Model(Position&& position,const char* modelFilename):Model(position,modelFilename){}

    virtual ~Model(){}

};


#endif
