#ifndef SimpleMouseBehaviorH
#define SimpleMouseBehaviorH
#include "../Component/Component.h"
#include "../Behavior/AbstractBehavior.h"


//TODO:this is almost a copy/paste of simpleKeyboardBehavior
class SimpleMouseBehavior: public AbstractBehavior{
  private:
    std::function<void(SDL_MouseButtonEvent)> callback;
  public:
	SimpleMouseBehavior(std::function<void(SDL_MouseButtonEvent)> callback){
        this->callback=callback;
    }
    
    virtual ~SimpleMouseBehavior(){}
    
    void  onMouseButtonDown(SDL_MouseButtonEvent button){
    	this->callback(button);
    }    


};
#endif
