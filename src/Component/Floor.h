#ifndef FloorH
#define FloorH

#include "Component.h"
#include <GL/gl.h>

class Floor: public Component { 
  const float SIDE_LENGTH=600.0f;//how far in Z axes will go.
  const float STEP_LENGTH=2.0f;
  public:
	Floor(Position* position):Component(position){}		

    virtual ~Floor(){}
    
    void render(){
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
