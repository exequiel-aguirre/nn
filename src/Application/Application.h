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
    void onPaint(){}    
    void onDestroy(){}
    void onKeyDown(SDL_Keycode key){
    	ListenerManager::getInstance()->callKeyboardListeners(key);
    }
    void onTimer(){
      ListenerManager::getInstance()->callTimerListeners();    
    }
    
    
    
    void onDraw(){
      if(currentComponent!=NULL) currentComponent->render();
    }
   
    
    void setCurrentComponent(Component* currentComponent){
      this->currentComponent=currentComponent;
    }
    
    
    
};
Application* Application::application=NULL;

#endif
