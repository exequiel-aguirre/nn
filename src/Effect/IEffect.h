#ifndef IEffectH
#define IEffectH



class IEffect{  
  public:
	IEffect(){}		

    virtual ~IEffect(){}    
    
	virtual void doEffect(){}
	virtual void undoEffect(){}


};
#endif

