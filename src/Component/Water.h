#ifndef WaterH
#define WaterH

#include "Surface.h"
#include "../Map/PlaneMap.h"
#include "../Map/CreasedDecorator.h"
#include <limits>

class Water: public Surface {
  public:
	  
	Water(Position&& position,float w,float h):Surface(position,CreasedDecorator(new PlaneMap(w,h)),"img/water.bmp"){}

    virtual ~Water(){}    
    
    void render(){
	    double reflectPlane[] = {0.0f, -1.0f, 0.0f, position.getY()-0.01};
		glEnable(GL_CLIP_PLANE0);
		glClipPlane(GL_CLIP_PLANE0, reflectPlane);
		//start reflection
		glPushMatrix();
			//translate everything since it will be reflection upside-down
			glTranslatef(0.0f, position.getY()*2.0f, 0.0f);
			//Flip everything upside-down
			glScalef(1.0, -1.0, 1.0);
			// Since the terrain is upside-down we need to do front-face culling.
			glCullFace(GL_FRONT);


			//Now we render all the things that reflect
			vector<Component*> childs=Application::getInstance()->getWorld().getChilds();
			vector<Component*>::iterator it;
			for(it=childs.begin();it!=childs.end();it++)
			{
				if((*it)->getReflects()){
					//(*it)->onBeforeRender();
					(*it)->render();
					//(*it)->onAfterRender();
				}
			}

		//Restore all the changes
		glCullFace(GL_BACK);
		glPopMatrix();
		glDisable(GL_CLIP_PLANE0);

		//Render the water with a blending effect
		glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);
			glColor4f(0.5f, 0.5f, 0.9f, 0.5f);
			Surface::render();
		glDisable(GL_BLEND);
    }

	float getMass(){
    	return std::numeric_limits<float>::max();
    }
};


#endif
