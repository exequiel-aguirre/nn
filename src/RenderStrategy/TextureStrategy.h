#ifndef TextureStrategyH
#define TextureStrategyH

#include "RenderStrategy3.h"
#include "../Utils/Utils.h"


class TextureStrategy :public RenderStrategy3 {
  private:
    GLuint  texture;
    char* defaultTextureFilename="img/ground.bmp";
    
  public:
    TextureStrategy(char* modelFilename,char* textureFilename):RenderStrategy3(modelFilename,GL_TRIANGLES){
        if(textureFilename==NULL) textureFilename=defaultTextureFilename;
        texture=Utils::loadTexture(textureFilename);
    }
	   TextureStrategy(IMap& map,char* textureFilename):RenderStrategy3(map,GL_TRIANGLES){
        if(textureFilename==NULL) textureFilename=defaultTextureFilename;
        texture=Utils::loadTexture(textureFilename);
    }

    virtual ~TextureStrategy(){}    
    
    
    void render(Position& position){
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D,texture);

      RenderStrategy3::render(position);

      glDisable(GL_TEXTURE_2D);
    }

};


#endif