#ifndef TextureStrategyH
#define TextureStrategyH
#include "CacheStrategy.h"
#include "../Utils/Utils.h"


class TextureStrategy :public CacheStrategy {   
  private:
    GLuint  texture;
    char* defaultTextureFilename="img/ground.bmp";
    
  public:
	   TextureStrategy(IMap* map,char* textureFilename):CacheStrategy(map,GL_QUAD_STRIP){
        if(textureFilename==NULL) textureFilename=defaultTextureFilename;
        texture=Utils::loadTexture(textureFilename);
    }

    virtual ~TextureStrategy(){}    
    
    
    void render(){
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D,texture);

      int i,j;
      for(i = 1; i <= lats; i++) 
      {       
       glBegin(GLMode);
         for(j = 0; j <= longs; j++) 
         {   
           glNormal3f(cachedValues[0][i-1][j][0],cachedValues[0][i-1][j][1],cachedValues[0][i-1][j][2]);
           glTexCoord2f(j%2,j%2);glVertex3f(cachedValues[0][i-1][j][0],cachedValues[0][i-1][j][1],cachedValues[0][i-1][j][2]);
           
           glNormal3f(cachedValues[0][i][j][0],cachedValues[0][i][j][1],cachedValues[0][i][j][2]);                  
           glTexCoord2f((j+1)%2,j%2);glVertex3f(cachedValues[0][i][j][0],cachedValues[0][i][j][1],cachedValues[0][i][j][2]);
         }
       glEnd();
      }

      glDisable(GL_TEXTURE_2D);
    }

};


#endif