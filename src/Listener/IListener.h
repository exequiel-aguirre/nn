#ifndef IListenerH
#define IListenerH

#include <SDL2/SDL_keyboard.h>

class IListener{
  public:
    IListener(){}
    
    
    virtual void onTimer(){}
    virtual void onCreate(){}
    virtual void onBeforeRender(){}
    virtual void render(){}
    virtual void onAfterRender(){}
    virtual void onKeyDown(SDL_Keycode key){}
    virtual void onKeyUp(SDL_Keycode key){}
    virtual void onMouseMotion(SDL_MouseMotionEvent motion){}
    virtual void onMouseButtonDown(SDL_MouseButtonEvent button){}
    virtual void onDestroy(){}

    

};
#endif
