#ifndef BlendingEffectH
#define BlendingEffectH
#include "IEffect.h"


class BlendingEffect:public IEffect{  
  public:
	BlendingEffect(){}		

    virtual ~BlendingEffect(){}
    

	void doEffect(){
		glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
    	glColor4f(1.0f,1.0f,1.0f,0.5f);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	}
	void undoEffect(){
		glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);    	
	}


};
#endif

