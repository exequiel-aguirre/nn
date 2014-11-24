#ifndef SurfaceH
#define SurfaceH

#include "Component.h"
#include "../Map/IMap.h"
#include "../RenderStrategy/IRenderStrategy.h"
#include "../RenderStrategy/CacheStrategy.h"
#include "../RenderStrategy/TextureStrategy.h"


class Surface: public Component {  
  
  public:
	  Surface(Position* position,IMap* map,GLenum GLMode):Component(position){		  		  
		  this->setRenderStrategy(new FastStrategy(map,GLMode));
	  }

	  Surface(Position* position,IMap* map,char* textureFilename):Component(position){		  		  
		  this->setRenderStrategy(new TextureStrategy(map,textureFilename));
	  }

    virtual ~Surface(){}


};


#endif


