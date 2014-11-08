#ifndef BoxH
#define BoxH

#include "Component.h"
#include <GL/gl.h>
#include <GL/glu.h>

//todo:make box a container
class Box: public Component {  
  private:
	GLuint	texture;
	char* defaultTextureFilename="img/box.bmp";
	
	void loadTexture(char* fileName){
		SDL_Surface* bmpFile=SDL_LoadBMP(fileName);		
		if(bmpFile == NULL ) std::cout <<  SDL_GetError();
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D,texture);
		glTexImage2D(GL_TEXTURE_2D,0,1,bmpFile->w,bmpFile->h,0,GL_RGB,GL_UNSIGNED_BYTE,bmpFile->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		
		SDL_FreeSurface(bmpFile);
	}
	
  public:
	  Box(Position* position,char* textureFilename):Component(position){
		  if(textureFilename==NULL) textureFilename=defaultTextureFilename;
		  loadTexture(textureFilename);		  
	  }		

    virtual ~Box(){}
    
    void render(){

			//pull this up			
			glTranslatef(this->position->getAbsoluteX(),this->position->getAbsoluteY(),this->position->getAbsoluteZ());	
			
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
			//we restore the position to avoid messing with the other's component's location
			//we can always draw them directly using the position on the glvertexinstruction above...
		   glTranslatef(-this->position->getAbsoluteX(),-this->position->getAbsoluteY(),-this->position->getAbsoluteZ());	
    }

};


#endif
