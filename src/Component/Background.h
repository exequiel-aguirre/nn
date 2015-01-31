#ifndef BackgroundH
#define BackgroundH

#include "Component.h"
#include "../Utils/Utils.h"
#include <GL/gl.h>


class Background: public Component {  	
  private:
  	GLuint  texture=false;
  	char* defaultTextureFilename="img/ground.bmp";
  	vector<float> color={0,0,0,1};
  public:
	  Background(char* textureFilename):Component(Position(0,0,0)){
		if(textureFilename==NULL) textureFilename=defaultTextureFilename;
        texture=Utils::loadTexture(textureFilename);
	  }
	  Background(vector<float> color):Component(Position(0,0,0)){
		this->color=color;		
	  }

	virtual ~Background(){}

	void onBeforeRenderFrame(){
		if(texture)
		{
			this->renderTexture();
		}
		else
		{
			this->renderColor();
		}
	}

	void renderColor(){
		glClearColor(color[0],color[1],color[2], color[3]);
	}

	void renderTexture(){
		//set the transformation matrices
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glOrtho(0,1,0,1,0,1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		//prepare to bind a texture
		glDepthMask(false);
		glEnable(GL_TEXTURE_2D);
		//bind the texture
		glBindTexture(GL_TEXTURE_2D,texture);
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);
			glVertex2f(0,0);
			glTexCoord2f(0,1);
			glVertex2f(0,1);
			glTexCoord2f(1,1);
			glVertex2f(1,1);
			glTexCoord2f(1,0);
			glVertex2f(1,0);
		glEnd();
		//restore the defaults
		glDisable(GL_TEXTURE_2D);
		glDepthMask(true);
		//restore the transformation matrices
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
};


#endif
