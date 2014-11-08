#ifndef GroundH
#define GroundH

#include "Component.h"
#include <GL/gl.h>
#include <GL/glu.h>

class Ground: public Component { 
  private:
	const float SIDE_LENGTH=50.0f;//how far in Z axes will go.
	const float STEP_LENGTH=10.0f;
	GLuint	texture;
	char* defaultTextureFilename="img/ground.bmp";

  public:
	Ground(Position* position,char* textureFilename):Component(position){
		if(textureFilename==NULL) textureFilename=defaultTextureFilename;
		texture=Utils::loadTexture(textureFilename);
	}

    virtual ~Ground(){}
    
    void render(){				
		// Set colour to white
		//glColor3ub(255, 255, 255);
	 	glBindTexture(GL_TEXTURE_2D,texture);
	 	float len=STEP_LENGTH/2;
		// Draw our ground grid
		glBegin(GL_QUADS);
			for (float lats = -SIDE_LENGTH; lats <= SIDE_LENGTH; lats += STEP_LENGTH)
			{
				for (GLint longs = -SIDE_LENGTH; longs <= SIDE_LENGTH; longs += STEP_LENGTH){
					//EXE-TODO:check how glTexCoord2f works, because I think that if I use 1 insead of len, 
					//is exactly the same
					//glNormal3f( 0.0f, -1.0f,-1.0f);
					glTexCoord2f(len,len); glVertex3f(-len+lats, this->position->getAbsoluteY(), -len+longs);
					glTexCoord2f(0.0f, len); glVertex3f( len+lats, this->position->getAbsoluteY(), -len+longs);
					glTexCoord2f(0.0f, 0.0f); glVertex3f( len+lats, this->position->getAbsoluteY(),  len+longs);
					glTexCoord2f(len, 0.0f); glVertex3f(-len+lats, this->position->getAbsoluteY(),  len+longs);
				}
			}
		glEnd();
	}

};


#endif
