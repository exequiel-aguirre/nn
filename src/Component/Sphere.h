#ifndef SphereH
#define SphereH

#include "Component.h"
#include <GL/gl.h>
#include <GL/glu.h>


class Sphere: public Component {  
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
	  Sphere(Position* position,char* textureFilename):Component(position){
		  if(textureFilename==NULL) textureFilename=defaultTextureFilename;
		  loadTexture(textureFilename);		  
	  }		

    virtual ~Sphere(){}
    
    void render(){
			
			//pull this up			
			glTranslatef(this->position->getAbsoluteX(),this->position->getAbsoluteY(),this->position->getAbsoluteZ());	

			float r=1.0;
			float theta;
			float phi0;
			float phi1;
			int lats=24;
			int longs=24;
			int i, j;
        	for(i = 0; i <= longs; i++) 
        	{
	           phi0= (2*M_PI/longs)* (i-1);
	           phi1= (2*M_PI/longs)* i;

	           glBegin(GL_QUAD_STRIP);
		           for(j = 0; j <= lats; j++) 
		           {   
					   theta=(2*M_PI/lats) * (j-1);
					   glNormal3f(r*cos(theta)*sin(phi0), r*sin(theta)*sin(phi0),r*cos(phi0));
		               glVertex3f(r*cos(theta)*sin(phi0), r*sin(theta)*sin(phi0),r*cos(phi0));
		               
		               glNormal3f(r*cos(theta)*sin(phi1), r*sin(theta)*sin(phi1),r*cos(phi1));		            
		               glVertex3f(r*cos(theta)*sin(phi1), r*sin(theta)*sin(phi1),r*cos(phi1));
		           }
	           glEnd();
			}
			//we restore the position to avoid messing with the other's component's location
			//we can always draw them directly using the position on the glvertexinstruction above...
		   glTranslatef(-this->position->getAbsoluteX(),-this->position->getAbsoluteY(),-this->position->getAbsoluteZ());	
    }

};


#endif
