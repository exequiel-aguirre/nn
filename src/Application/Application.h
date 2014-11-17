#ifndef ApplicationH
#define ApplicationH

#include "../Listener/IListener.h"
#include "../Listener/ListenerManager.h"
#include "../Component/Component.h"
#include <vector>


class Application:public IListener {
  private:    
    //todo:this should be an special component like a container
    Component* currentComponent;   
    static Application* application;    
    
    Application(){
      this->currentComponent=NULL;      
    }
    
  public:   
    
    static Application* getInstance(){
      if(application==NULL) application=new Application();
      return application;
    }
    
    virtual ~Application(){}	    
    
    void onCreate(){}
    void onDestroy(){}
    void onKeyDown(SDL_Keycode key){
    	ListenerManager::getInstance()->callKeyboardListeners(key);
    }
    void onTimer(){
      ListenerManager::getInstance()->callTimerListeners();    
    }
    void onMouseMotion(SDL_MouseMotionEvent motion){
      ListenerManager::getInstance()->callMouseListeners(motion);
    }
    
    void render(){
      if(currentComponent!=NULL)
      {
        currentComponent->onBeforeRenderFrame();
        currentComponent->onBeforeRender();
        currentComponent->render();
        currentComponent->onAfterRender();
      }
    }
   
    
    void setCurrentComponent(Component* currentComponent){
      this->currentComponent=currentComponent;
    }
    
    
    
};
Application* Application::application=NULL;

#endif
