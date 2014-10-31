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
    void virtual onKeyDown(SDLKey key){}
    void virtual onDestroy(){}

    

};
#endif
