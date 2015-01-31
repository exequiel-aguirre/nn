#ifndef FogH
#define FogH

#include "IEffect.h"
#include <GL/gl.h>

class Fog: public IEffect { 	
  private:	
	GLfloat color[4]= {0.5f, 0.5f, 0.5f, 1.0f};  
  public:
	  Fog(){
		glClearColor(color[0],color[1],color[2],color[3]);//the fog looks better with the background color changed
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogfv(GL_FOG_COLOR, color);
		glFogf(GL_FOG_DENSITY, 0.05f);
		glHint(GL_FOG_HINT, GL_DONT_CARE);
		glFogf(GL_FOG_START, 100.0f);
		glFogf(GL_FOG_END, 110.0f);
		glEnable(GL_FOG);
	  }		

    virtual ~Fog(){}    

};


#endif
