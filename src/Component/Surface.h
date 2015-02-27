#ifndef SurfaceH
#define SurfaceH

#include "Component.h"
#include "../Map/IMap.h"
#include "../RenderStrategy/RenderStrategy.h"

class Surface: public Component {  
  
  public:
	  Surface(Position position,IMap&& map,GLenum GLMode):Component(position,new RenderStrategy(map,NULL,GLMode)){}

	  Surface(Position position,IMap&& map,char* textureFilename):Component(position,new RenderStrategy(map,textureFilename,GL_TRIANGLES)){}

	  Surface(Position position,IMap&& map,char* textureFilename,GLenum GLMode,char* shaderName):Component(position,new RenderStrategy(map,textureFilename,GLMode,shaderName)){}

    virtual ~Surface(){}


};


#endif


