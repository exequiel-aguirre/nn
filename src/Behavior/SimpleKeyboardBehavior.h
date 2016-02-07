#ifndef SimpleKeyboardBehaviorH
#define SimpleKeyboardBehaviorH
#include "../Component/Component.h"
#include "../Behavior/AbstractBehavior.h"



class SimpleKeyboardBehavior: public AbstractBehavior{
  private:
    std::function<void(SDL_Keycode)> onKeyDownCallback;
    std::function<void(SDL_Keycode)> onKeyUpCallback;
  public:
	SimpleKeyboardBehavior(std::function<void(SDL_Keycode)> onKeyDownCallback,std::function<void(SDL_Keycode)> onKeyUpCallback){
        this->onKeyDownCallback=onKeyDownCallback;
        this->onKeyUpCallback=onKeyUpCallback;
    }
    
    
    void  onKeyDown(SDL_Keycode key){
      this->onKeyDownCallback(key);
    }
    void  onKeyUp(SDL_Keycode key){
      this->onKeyUpCallback(key);
    }    


};
#endif
