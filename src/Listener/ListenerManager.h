#ifndef ListenerManagerH
#define ListenerManagerH
#include <vector>

class ListenerManager{
  private:
    static ListenerManager* instance;
    
    vector<IListener*>* listeners;
    ListenerManager(){
      listeners=new vector<IListener*>();
    }
    
    
   public:
    static ListenerManager* getInstance(){
      if(instance == NULL) instance=new ListenerManager();
      return instance;
    }
    virtual ~ListenerManager(){}	
    
    //TODO:make this call methods generic
    void callTimerListeners(){
      vector<IListener*>::iterator it;
      for(it=listeners->begin();it!=listeners->end();it++){
        (*it)->onTimer();
      }    
    }    
    void callKeyboardListeners(SDLKey key){
    	vector<IListener*>::iterator it;
    	for(it=listeners->begin();it!=listeners->end();it++){
    		(*it)->onKeyDown(key) ;
    	}
    }

    void add(IListener* listener){
      listeners->push_back(listener);      
    }









};
ListenerManager* ListenerManager::instance=NULL;

#endif


