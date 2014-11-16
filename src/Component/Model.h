#ifndef ModelH
#define ModelH

#include "Component.h"
#include "../RenderStrategy/TextureStrategy.h"



class Model: public Component {  
  protected:  	
	IRenderStrategy* renderStrategy;

  public:
  	 Model(Position* position,IRenderStrategy* renderStrategy):Component(position){
	  	this->renderStrategy=renderStrategy;
	  }
	  Model(Position* position,char* modelFilename):Model(position,new TextureStrategy(modelFilename,"img/human.bmp")){}	  

    virtual ~Model(){}
    
    void render(){
    		
			//pull this up			
			glTranslatef(this->position->getAbsoluteX(),this->position->getAbsoluteY(),this->position->getAbsoluteZ());	
			
			this->renderStrategy->render();
			//we restore the position to avoid messing with the other's component's location
			//we can always draw them directly using the position on the glvertexinstruction above...
		   glTranslatef(-this->position->getAbsoluteX(),-this->position->getAbsoluteY(),-this->position->getAbsoluteZ());	
    }

};


#endif
