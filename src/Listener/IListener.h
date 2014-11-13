#ifndef IListenerH
#define IListenerH

#include <SDL2/SDL_keyboard.h>

class IListener{
  public:
    IListener(){}
    virtual ~IListener(){}
    
    
    virtual void onTimer(){}
    virtual void onCreate(){}
    virtual void onBeforeRender(){}
    virtual void render(){}
    virtual void onAfterRender(){}
    virtual void onKeyDown(SDL_Keycode key){}
    virtual void onMouseMotion(SDL_MouseMotionEvent motion){}
    virtual void onDestroy(){}

    

};
#endif
