#ifndef ModelH
#define ModelH

#include "Component.h"
#include "../Utils/Utils.h"
#include "../DataStructure/ModelObject.h"



class Model: public Component {

  public:
	Model(Position& position,const char* modelFilename,const char* textureFilename):Component(position,Utils::loadModel(modelFilename),textureFilename,GL_TRIANGLES){}
	Model(Position&& position,const char* modelFilename,const char* textureFilename):Model(position,modelFilename,textureFilename){}


};


#endif
