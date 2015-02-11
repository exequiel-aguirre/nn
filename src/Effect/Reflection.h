#ifndef ReflectionH
#define ReflectionH
#include "IEffect.h"


class Reflection:public IEffect{  
  public:
	Reflection(){}		

    virtual ~Reflection(){}
    

	void doEffect(){
		//this is not ok...
		float reflectionY=Application::getInstance()->getWorld().getPosition().getY();
		
		double reflectPlane[] = {0.0f, -1.0f, 0.0f, reflectionY};
		glEnable(GL_CLIP_PLANE0);
		glClipPlane(GL_CLIP_PLANE0, reflectPlane);
		//start reflection
		glPushMatrix();
			//translate everything since it will be reflection upside-down
			glTranslatef(0.0f, reflectionY*2.0f, 0.0f);
			//Flip everything upside-down
			glScalef(1.0, -1.0, 1.0);
			// Since the terrain is upside-down we need to do front-face culling.
			glCullFace(GL_FRONT);
			//Now we render all the reflections
			vector<Component*>::iterator it;
			vector<Component*> worldChilds=Application::getInstance()->getWorld().getChilds();
			for(it=worldChilds.begin();it!=worldChilds.end();it++)
			{
				if((*it)->getReflects()){         
					(*it)->onBeforeRender();
					(*it)->render();
					(*it)->onAfterRender();
				}
			}
			//Restore all the changes
			glCullFace(GL_BACK);
		glPopMatrix();
		glDisable(GL_CLIP_PLANE0);
	}

	void undoEffect(){
		//do nothing
	}


};
#endif

