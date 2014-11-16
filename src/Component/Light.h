#ifndef LightH
#define LightH

#include "Component.h"
#include <GL/gl.h>


class Light: public Component { 	
  private:
  	bool isLightEnabled=false;
	GLfloat lightAmbient[4]= { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat lightDiffuse[4]= { 1.0f, 1.0f, 1.0f, 1.0f };	
  
  public:
	  Light(Position* position):Component(position){	  	
		glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);

		GLfloat lightPosition[4]={position->getAbsoluteX(),position->getAbsoluteY(),position->getAbsoluteZ(),1.0f};
		glLightfv(GL_LIGHT1, GL_POSITION,lightPosition);
		glEnable(GL_LIGHT1);

		//turn off the light
		toggleLight();
		
	  }		

    virtual ~Light(){}

    void toggleLight()
	{
		if(!isLightEnabled)
		{
			glEnable(GL_LIGHTING);
		}
		else
		{
			glDisable(GL_LIGHTING);
		}
	}

};


#endif
