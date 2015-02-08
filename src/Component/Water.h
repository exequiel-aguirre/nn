#ifndef WaterH
#define WaterH

#include "Surface.h"
#include "../Map/PlaneMap.h"
#include "../Map/CreasedDecorator.h"
#include <limits>

class Water: public Container {
  private:
	bool reflects=true;
  public:
	  
	Water(Position position,float w,float h,bool reflects):Container(position){
		add(new Surface(Position(0,0,0),CreasedDecorator(new PlaneMap(w,h)),"img/water.bmp"));
		this->reflects=reflects;
	}
	Water(Position position,float w,float h):Water(position,w,h,true){}

    virtual ~Water(){}    
    
    void render(){
		if(this->reflects){
			this->renderReflections();
			this->renderWater();
			this->renderComponents();
		}
		else{
			//we need to use this swap the order so the blend works
			this->renderComponents();
			this->renderWater();
		}
    }

    void renderReflections(){
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


			//Now we render all the reflections
			vector<Component*>::iterator it;
			for(it=this->childs.begin()+1;it!=this->childs.end();it++)
			{
				(*it)->onBeforeRender();
				(*it)->render();
				(*it)->onAfterRender();
			}

			//Restore all the changes
			glCullFace(GL_BACK);

		glPopMatrix();
		glDisable(GL_CLIP_PLANE0);
    }

    void renderWater(){
		//Render the water with a blending effect
		glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);
			glColor4f(0.5f, 0.5f, 0.9f, 0.5f);
			this->childs[0]->onBeforeRender();//The first component MUST be the water
			this->childs[0]->render();
			this->childs[0]->onAfterRender();
		glDisable(GL_BLEND);

    }

    void renderComponents(){
		//and now we render the other components  like we do normally
		vector<Component*>::iterator it;
		for(it=this->childs.begin()+1;it!=this->childs.end();it++)
		{
			(*it)->onBeforeRender();
			(*it)->render();
			(*it)->onAfterRender();
		}
    }

	float getMass(){
    	return std::numeric_limits<float>::max();
    }
};


#endif
