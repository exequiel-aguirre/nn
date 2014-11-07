#ifndef SurfaceH
#define SurfaceH

#include "Component.h"
#include <GL/gl.h>
#include "../Map/IMap.h"
#include "../RenderStrategy/IRenderStrategy.h"
#include "../RenderStrategy/CacheStrategy.h"
#include <iostream>


class Surface: public Component {  
  private:		
	IRenderStrategy* renderStrategy;
  
  public:
	  Surface(Position* position,IMap* map,GLenum GLMode):Component(position){		  		  
		  this->renderStrategy=new CacheStrategy(map,GLMode);
	  }		

    virtual ~Surface(){}
    
    void render(){			
		//position the rendering
		glTranslatef(this->position->getAbsoluteX(),this->position->getAbsoluteY(),this->position->getAbsoluteZ());			
		this->renderStrategy->render();
		//we restore the position to avoid messing with the other's component's location			
		glTranslatef(-this->position->getAbsoluteX(),-this->position->getAbsoluteY(),-this->position->getAbsoluteZ());	
    }


    


};


#endif


