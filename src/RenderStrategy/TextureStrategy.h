#ifndef TextureStrategyH
#define TextureStrategyH
#include "CacheStrategy.h"


class TextureStrategy :public CacheStrategy {   
  private:
    GLuint  texture;
    char* defaultTextureFilename="img/ground.bmp";

    void loadTexture(char* filename){
      SDL_Surface* bmpFile=SDL_LoadBMP(filename);   
      if(bmpFile == NULL ) std::cout <<  SDL_GetError();
      glGenTextures(1,&texture);
      glBindTexture(GL_TEXTURE_2D,texture);
      glTexImage2D(GL_TEXTURE_2D,0,3,bmpFile->w,bmpFile->h,0,GL_RGB,GL_UNSIGNED_BYTE,bmpFile->pixels);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      SDL_FreeSurface(bmpFile);
    }
  public:
	   TextureStrategy(IMap* map,char* textureFilename):CacheStrategy(map,GL_QUAD_STRIP){
        if(textureFilename==NULL) textureFilename=defaultTextureFilename;
        loadTexture(textureFilename);
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