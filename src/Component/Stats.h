#ifndef StatsH
#define StatsH

#include "Component.h"

class Stats: public Component {
  private:  	
  Uint32 lastTime = SDL_GetTicks();
  Uint32 frameTime = SDL_GetTicks();
  Uint32 frames = 0; //frames passed since the last recorded fps.

  public:
	  Stats():Component(Position()){
      setReflects(false);
    }

    void render(){
      frames++;
      Uint32 lastFrameTime=frameTime;
      frameTime=SDL_GetTicks();
      if (lastTime < SDL_GetTicks() - 1000)
      {
        lastTime = SDL_GetTicks();
        std::cout <<"\rFPS: "<< frames<<"  Frame Time: "<<(frameTime-lastFrameTime)<<"ms"<<std::flush;
        frames = 0;
      }
    }
};


#endif
