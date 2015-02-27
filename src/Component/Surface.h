#ifndef SurfaceH
#define SurfaceH

#include "Component.h"
#include "../Map/IMap.h"
#include "../DataStructure/ModelObject.h"

class Surface: public Component {  
  
  public:
	  Surface(Position position,IMap&& map,GLenum GLMode):Component(position,ModelObject(map),GLMode){}

	  Surface(Position position,IMap&& map,char* textureFilename):Component(position,ModelObject(map),textureFilename,GL_TRIANGLES){}

	  Surface(Position position,IMap&& map,char* textureFilename,GLenum GLMode,char* shaderName):Component(position,ModelObject(map),textureFilename,GLMode,shaderName){}

    virtual ~Surface(){}


};


#endif


