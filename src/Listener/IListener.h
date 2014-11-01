#ifndef IListenerH
#define IListenerH

#include <SDL2/SDL_keyboard.h>

class IListener{
  public:
    IListener(){}
    virtual ~IListener(){}
    
    
    void virtual onTimer(){}
    void virtual onCreate(){}
    void virtual onPaint(){}
    void virtual onDraw(){}
    void virtual onKeyDown(SDL_Keycode key){}
    void virtual onDestroy(){}

    

};
#endif
