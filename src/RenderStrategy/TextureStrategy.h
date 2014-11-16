#ifndef TextureStrategyH
#define TextureStrategyH

#include "CacheStrategy.h"
#include "../Utils/Utils.h"


class TextureStrategy :public CacheStrategy {   
  private:
    GLuint  texture;
    char* defaultTextureFilename="img/ground.bmp";
    
  public:
    TextureStrategy(char* modelFilename,char* textureFilename):CacheStrategy(modelFilename,GL_TRIANGLES){
        if(textureFilename==NULL) textureFilename=defaultTextureFilename;
        texture=Utils::loadTexture(textureFilename);
    }
	   TextureStrategy(IMap* map,char* textureFilename):CacheStrategy(map,GL_TRIANGLES){
        if(textureFilename==NULL) textureFilename=defaultTextureFilename;
        texture=Utils::loadTexture(textureFilename);
    }

    virtual ~TextureStrategy(){}    
    
    
    void render(){
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D,texture);

      CacheStrategy::render();

      glDisable(GL_TEXTURE_2D);
    }

};


#endif