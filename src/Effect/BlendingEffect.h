#ifndef BlendingEffectH
#define BlendingEffectH
#include "IEffect.h"


class BlendingEffect:public IEffect{  
  public:
	BlendingEffect(){}		

    virtual ~BlendingEffect(){}
    

	void doEffect(){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	}
	void undoEffect(){
		glDisable(GL_BLEND);
	}


};
#endif

