#ifndef IListenerH
#define IListenerH

#include <SDL2/SDL_keyboard.h>

class IListener{
  public:
    IListener(){}
    virtual ~IListener(){}
    
    
    void virtual onTimer(){}
    void virtual onCreate(){}    
    void virtual onDraw(){}
    void virtual onKeyDown(SDL_Keycode key){}
    void virtual onMouseMotion(SDL_MouseMotionEvent motion){}
    void virtual onDestroy(){}

    

};
#endif
