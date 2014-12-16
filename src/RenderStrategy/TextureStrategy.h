#ifndef TextureStrategyH
#define TextureStrategyH

#include "FastStrategy.h"
#include "../Utils/Utils.h"


class TextureStrategy :public FastStrategy {   
  private:
    GLuint  texture;
    char* defaultTextureFilename="img/ground.bmp";
    
  public:
    TextureStrategy(char* modelFilename,char* textureFilename):FastStrategy(modelFilename,GL_TRIANGLES){
        if(textureFilename==NULL) textureFilename=defaultTextureFilename;
        texture=Utils::loadTexture(textureFilename);
    }
	   TextureStrategy(IMap& map,char* textureFilename):FastStrategy(map,GL_TRIANGLES){
        if(textureFilename==NULL) textureFilename=defaultTextureFilename;
        texture=Utils::loadTexture(textureFilename);
    }

    virtual ~TextureStrategy(){}    
    
    
    void render(){
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D,texture);

      FastStrategy::render();

      glDisable(GL_TEXTURE_2D);
    }

};


#endif