#ifndef LightH
#define LightH

#include "Component.h"
#include <GL/gl.h>


class Light: public Component { 	
  private:
	bool isLightEnabled=false;
	GLfloat lightAmbient[4]= { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat lightDiffuse[4]= { 0.75f, 0.75f, 0.75f, 1.0f };
	GLfloat lightSpecular[4]={ 1.0f, 1.0f, 1.0f, 1.0f};
  
  public:
	  Light(Position&& position):Component(position){
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, lightSpecular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0f);

		glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

		GLfloat lightPosition[4]={position.getX(),position.getY(),position.getZ(),1.0f};
		glLightfv(GL_LIGHT0, GL_POSITION,lightPosition);
		glEnable(GL_LIGHT0);

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
