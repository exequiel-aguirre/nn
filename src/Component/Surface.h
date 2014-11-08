#ifndef SurfaceH
#define SurfaceH

#include "Component.h"
#include <GL/gl.h>
#include "../Map/IMap.h"
#include "../RenderStrategy/IRenderStrategy.h"
#include "../RenderStrategy/CacheStrategy.h"
#include "../RenderStrategy/TextureStrategy.h"
#include <iostream>


class Surface: public Component {  
  private:		
	IRenderStrategy* renderStrategy;
  
  public:
	  Surface(Position* position,IMap* map,GLenum GLMode):Component(position){		  		  
		  this->renderStrategy=new CacheStrategy(map,GLMode);
	  }

	  Surface(Position* position,IMap* map,char* textureFilename):Component(position){		  		  
		  this->renderStrategy=new TextureStrategy(map,textureFilename);
	  }

    virtual ~Surface(){}
    
    void render(){    	
		//position the rendering
		glTranslatef(this->position->getAbsoluteX(),this->position->getAbsoluteY(),this->position->getAbsoluteZ());			
		glDisable(GL_TEXTURE_2D);//This should be the other way around!!! enable,use texture and disable.
		this->renderStrategy->render();
		glEnable(GL_TEXTURE_2D);
		//we restore the position to avoid messing with the other's component's location			
		glTranslatef(-this->position->getAbsoluteX(),-this->position->getAbsoluteY(),-this->position->getAbsoluteZ());	
    }


    


};


#endif


