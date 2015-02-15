#ifndef SurfaceH
#define SurfaceH

#include "Component.h"
#include "../Map/IMap.h"
#include "../RenderStrategy/IRenderStrategy.h"
#include "../RenderStrategy/CacheStrategy.h"
#include "../RenderStrategy/TextureStrategy.h"
#include "../RenderStrategy/RenderStrategy3.h"


class Surface: public Component {  
  
  public:
	  Surface(Position position,IMap&& map,GLenum GLMode):Component(position,new TextureStrategy(map,NULL)){}

	  Surface(Position position,IMap&& map,char* textureFilename):Component(position,new TextureStrategy(map,textureFilename)){}

    virtual ~Surface(){}


};


#endif


