#ifndef SurfaceH
#define SurfaceH

#include "Component.h"
#include "../Map/IMap.h"
#include "../RenderStrategy/IRenderStrategy.h"
#include "../RenderStrategy/CacheStrategy.h"
#include "../RenderStrategy/TextureStrategy.h"


class Surface: public Component {  
  private:		
	IRenderStrategy* renderStrategy;
  
  public:
	  Surface(Position* position,IMap* map,GLenum GLMode):Component(position){		  		  
		  this->renderStrategy=new FastStrategy(map,GLMode);
	  }

	  Surface(Position* position,IMap* map,char* textureFilename):Component(position){		  		  
		  this->renderStrategy=new TextureStrategy(map,textureFilename);
	  }

    virtual ~Surface(){}
    
    void render(){
		this->renderStrategy->render();
    }


    


};


#endif


