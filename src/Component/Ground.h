#ifndef GroundH
#define GroundH

#include "Component.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "../Behavior/BaseTranslationKeyboardBehavior.h"
#include "../Behavior/BaseRotationKeyboardBehavior.h"


class Ground: public Component { 
  const float SIDE_LENGTH=600.0f;//how far in Z axes will go.
  const float STEP_LENGTH=2.0f;
  public:
	Ground(Position* position):Component(position){}		

    virtual ~Ground(){}
    
    void onRender(){		
		//glLoadIdentity();
		//pull this up			
		//glTranslatef(this->position->getAbsoluteX(),this->position->getAbsoluteY(),this->position->getAbsoluteZ());		
		
		// Set colour to white
		glColor3ub(255, 255, 255);
	 
		// Draw our ground grid
		glBegin(GL_LINES);
			for (GLint loop = -SIDE_LENGTH; loop < SIDE_LENGTH; loop += STEP_LENGTH)
			{
				// Draw lines along Z-Axis
				glVertex3f(loop, this->position->getAbsoluteY(),  SIDE_LENGTH);
				glVertex3f(loop, this->position->getAbsoluteY(), -SIDE_LENGTH);
		 
				// Draw lines across X-Axis
				glVertex3f(-SIDE_LENGTH, this->position->getAbsoluteY(), loop);
				glVertex3f( SIDE_LENGTH, this->position->getAbsoluteY(), loop);
			}
		glEnd();
	}

};


#endif
