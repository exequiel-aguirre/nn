#ifndef ReflectionH
#define ReflectionH
#include "IEffect.h"


class Reflection:public IEffect{  
  public:
	Reflection(){}		

    virtual ~Reflection(){}
    

	void doEffect(){
		/*TODO:here we are supposed to transform the reflectPlane 0,-1,0,0 by the inverse of the viewMatrix
		* What we are doing is taking the second row of the inverse of the viewMatrix and multiplying by -1
		*/
		Matrix viewMatrixInverse=RenderStrategy::getInstance().getViewMatrix().getInverse();
		float reflectPlane[4]={-viewMatrixInverse[4],-viewMatrixInverse[5],-viewMatrixInverse[6],-viewMatrixInverse[7]};
		RenderStrategy::getInstance().setReflectPlane(reflectPlane);
		glEnable(GL_CLIP_PLANE0);
			Matrix& viewMatrix=RenderStrategy::getInstance().getViewMatrix();
			viewMatrix.scale(1.0,-1.0,1.0);
			RenderStrategy::getInstance().setViewMatrix(viewMatrix);
			//Now we render all the reflections
			vector<Component*>::iterator it;
			vector<Component*> worldChilds=Application::getInstance().getWorld().getChilds();
			for(it=worldChilds.begin();it!=worldChilds.end();it++)
			{
				if((*it)->getReflects())
				{
					(*it)->render();
				}
			}
			//Restore all the changes
			viewMatrix.scale(1.0,-1.0,1.0);
			RenderStrategy::getInstance().setViewMatrix(viewMatrix);
		glDisable(GL_CLIP_PLANE0);
	}

	void undoEffect(){
		//do nothing
	}


};
#endif

