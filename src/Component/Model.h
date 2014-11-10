#ifndef ModelH
#define ModelH

#include "Component.h"
#include <GL/gl.h>
#include "../Utils/Utils.h"
#include "../Utils/ModelObject.h"
#include <vector>
using std::vector;


class Model: public Component {  
  private:
	GLuint	texture;
	char* defaultTextureFilename="img/box.bmp";
	ModelObject* modelObject;

  public:
	  Model(Position* position,char* textureFilename):Component(position){
		//if(textureFilename==NULL) textureFilename=defaultTextureFilename;
		//texture=Utils::loadTexture(textureFilename);
	  	modelObject=Utils::loadModel(textureFilename);

	  }		

    virtual ~Model(){}
    
    void render(){
    		
			//pull this up			
			glTranslatef(this->position->getAbsoluteX(),this->position->getAbsoluteY(),this->position->getAbsoluteZ());	
			
			//bind the texture
			//glBindTexture(GL_TEXTURE_2D,texture);
			float* point;
			glBegin(GL_TRIANGLES);				
    			for(int i=0;i<modelObject->getSize();i++)
    			{
    				point=modelObject->getNormal(i);
    				glNormal3f(point[0],point[1],point[2]);
    				point=modelObject->getVertex(i);
					glVertex3f(point[0],point[1],point[2]);    				
    			}			
				
			glEnd();
			//we restore the position to avoid messing with the other's component's location
			//we can always draw them directly using the position on the glvertexinstruction above...
		   glTranslatef(-this->position->getAbsoluteX(),-this->position->getAbsoluteY(),-this->position->getAbsoluteZ());	
    }

};


#endif
