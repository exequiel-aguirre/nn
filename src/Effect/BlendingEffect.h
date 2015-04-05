#ifndef BlendingEffectH
#define BlendingEffectH
#include "IEffect.h"


class BlendingEffect:public IEffect{  
  public:
	BlendingEffect(){
		glBlendFunc(GL_ONE_MINUS_DST_COLOR,GL_ONE);
	}

    virtual ~BlendingEffect(){}
    

	void doEffect(){
		glEnable(GL_BLEND);
	}
	void undoEffect(){
		glDisable(GL_BLEND);
	}


};
#endif

