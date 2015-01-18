#ifndef ApplicationH
#define ApplicationH

#include "../Listener/IListener.h"
#include "../Listener/ListenerManager.h"
#include "../Component/Container.h"
#include <vector>


class Application:public IListener {
  private:
    Container world=Container(Position(0,0,0));
    static Application* application;    
    
    Application(){}
    
  public:   
    
    static Application* getInstance(){
      if(application==NULL) application=new Application();
      return application;
    }
    
    virtual ~Application(){}	    
    
    void onCreate(){}
    void onDestroy(){}
    void onKeyboardEvent(SDL_KeyboardEvent keyEvent){
      ListenerManager::getInstance()->callKeyboardListeners(keyEvent);
    }
    void onTimer(){
      ListenerManager::getInstance()->callTimerListeners();    
    }
    void onMouseMotionEvent(SDL_MouseMotionEvent motion){
      ListenerManager::getInstance()->callMouseListeners(motion);
    }
    void onMouseButtonEvent(SDL_MouseButtonEvent button){
      ListenerManager::getInstance()->callMouseListeners(button);
    }
    
    void render(){
        world.onBeforeRenderFrame();
        world.onBeforeRender();
        world.render();
        world.onAfterRender();
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
Application* Application::application=NULL;

#endif
