#ifndef BoxH
#define BoxH

#include "Component.h"
#include <GL/gl.h>
#include "../Utils/Utils.h"

//todo:make box a container
class Box: public Component {  
  private:
	GLuint	texture;
	char* defaultTextureFilename="img/box.bmp";
	
  public:
	  Box(Position* position,char* textureFilename):Component(position){
		  if(textureFilename==NULL) textureFilename=defaultTextureFilename;
		  texture=Utils::loadTexture(textureFilename);
	  }		

    virtual ~Box(){}
    
    void render(){
			glEnable(GL_TEXTURE_2D);
			//bind the texture
			glBindTexture(GL_TEXTURE_2D,texture);
			//draw the box
			glBegin(GL_QUADS);
					// Front Face
					glNormal3f( 0.0f, 0.0f,1.0f);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
					// Back Face
					glNormal3f( 0.0f, 0.0f,-1.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
					glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
					glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
					// Top Face
					glNormal3f( 0.0f, 1.0f,0.0f);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
					// Bottom Face
					glNormal3f( 0.0f, -1.0f,-1.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
					glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
					glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
					// Right face
					glNormal3f( 1.0f, 0.0f,-1.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
					glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
					glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
					// Left Face
					glNormal3f( -1.0f, 0.0f,-1.0f);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
				glEnd();
			glDisable(GL_TEXTURE_2D);
    }

};


#endif
