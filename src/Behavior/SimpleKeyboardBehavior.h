#ifndef SimpleKeyboardBehaviorH
#define SimpleKeyboardBehaviorH
#include "../Component/Component.h"
#include "../Behavior/AbstractBehavior.h"



class SimpleKeyboardBehavior: public AbstractBehavior{
  private:
    std::function<void(SDL_Keycode)> callback;
  public:
	SimpleKeyboardBehavior(std::function<void(SDL_Keycode)> callback){
        this->callback=callback;
    }
    
    virtual ~SimpleKeyboardBehavior(){}
    
    void  onKeyDown(SDL_Keycode key){
    	this->callback(key);
    }    


};
#endif
