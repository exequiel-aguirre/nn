#ifndef ApplicationH
#define ApplicationH

#include "../Listener/IListener.h"
#include "../Listener/ListenerManager.h"
#include "../Component/Container.h"
#include <vector>


class Application:public IListener {
  private:
    Container world=Container(Position(0,0,0));
    
    Application(){}
    
  public:   
    //for Singletons we are using static local, so the destructor is called when the program exits
    static Application& getInstance(){
      static Application application;
      return application;
    }

    ~Application(){
      world.destroy();
    }
    
    void onCreate(){}
    void onDestroy(){}
    void onKeyboardEvent(SDL_KeyboardEvent keyEvent){
      ListenerManager::getInstance().callKeyboardListeners(keyEvent);
    }
    void onTimer(){
      ListenerManager::getInstance().callTimerListeners();
    }
    void onMouseMotionEvent(SDL_MouseMotionEvent motion){
      ListenerManager::getInstance().callMouseListeners(motion);
    }
    void onMouseButtonEvent(SDL_MouseButtonEvent button){
      ListenerManager::getInstance().callMouseListeners(button);
    }
    
    void render(){
        world.onBeforeRenderFrame();
        world.render();
    }
   
    void setWorld(Container&& world){
      setWorld(world);
    }
    void setWorld(Container& world){
      this->world=world;
    }

    Container& getWorld(){
      return world;
    }

};

#endif
