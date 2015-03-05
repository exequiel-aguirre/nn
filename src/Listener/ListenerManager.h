#ifndef ListenerManagerH
#define ListenerManagerH
#include <vector>
using std::vector;

class ListenerManager{
  private:
    static ListenerManager* instance;
    
    vector<IListener*> listeners;
    ListenerManager(){
      listeners.reserve(20);//weird bugfix
    }
    
    
   public:
    static ListenerManager& getInstance(){
      if(instance == NULL) instance=new ListenerManager();
      return *instance;
    }
    virtual ~ListenerManager(){}	
    


    void callMouseListeners(SDL_MouseMotionEvent motion){
      vector<IListener*>::iterator it;
      for(it=listeners.begin();it!=listeners.end();it++){
        (*it)->onMouseMotion(motion);
      }
    }

    void callMouseListeners(SDL_MouseButtonEvent button){
      vector<IListener*>::iterator it;
      for(it=listeners.begin();it!=listeners.end();it++){
        (*it)->onMouseButtonDown(button);
      }
    }

    //TODO:make this call methods generic
    void callTimerListeners(){
      vector<IListener*>::iterator it;
      for(it=listeners.begin();it!=listeners.end();it++){
        (*it)->onTimer();
      }    
    }    
    void callKeyboardListeners(SDL_KeyboardEvent keyEvent){
      vector<IListener*>::iterator it;
      for(it=listeners.begin();it!=listeners.end();it++){
        if(keyEvent.type==SDL_KEYDOWN )(*it)->onKeyDown(keyEvent.keysym.sym);
        if(keyEvent.type==SDL_KEYUP )(*it)->onKeyUp(keyEvent.keysym.sym);
      }
    }

    void add(IListener* listener){
      listeners.push_back(listener);
    }









};
ListenerManager* ListenerManager::instance=NULL;

#endif


