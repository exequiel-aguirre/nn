#ifndef ListenerManagerH
#define ListenerManagerH
#include <vector>
using std::vector;

class ListenerManager{
  private:
    static ListenerManager* instance;
    
    vector<IListener*> listeners;
    ListenerManager(){}
    
    
   public:
    static ListenerManager* getInstance(){
      if(instance == NULL) instance=new ListenerManager();
      return instance;
    }
    virtual ~ListenerManager(){}	
    


    void callMouseListeners(SDL_MouseMotionEvent motion){
      vector<IListener*>::iterator it;
      for(it=listeners.begin();it!=listeners.end();it++){
        (*it)->onMouseMotion(motion);
      }
    }

    //TODO:make this call methods generic
    void callTimerListeners(){
      vector<IListener*>::iterator it;
      for(it=listeners.begin();it!=listeners.end();it++){
        (*it)->onTimer();
      }    
    }    
    void callKeyboardListeners(SDL_Keycode key){
      vector<IListener*>::iterator it;
      for(it=listeners.begin();it!=listeners.end();it++){
        (*it)->onKeyDown(key) ;
      }
    }

    void add(IListener* listener){
      listeners.push_back(listener);
    }









};
ListenerManager* ListenerManager::instance=NULL;

#endif


