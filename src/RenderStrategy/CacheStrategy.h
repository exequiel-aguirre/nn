#ifndef CacheStrategyH
#define CacheStrategyH
#include "IRenderStrategy.h"


class CacheStrategy :public IRenderStrategy {  
  private:
    const int LATITUDE_MODE=0;
    const int LONGITUDE_MODE=1;

  protected:
    float cachedValues[2][MAX_STEP][MAX_STEP][3]={};
    IMap* map;
    GLenum GLMode;

  public:
	CacheStrategy(IMap* map,GLenum GLMode){
        this->map=map;
        this->GLMode=GLMode;        
        this->buildCachedMap();
    }

    virtual ~CacheStrategy(){}    
    
    void render(){      
      render(LATITUDE_MODE);
      if(GLMode==GL_QUAD_STRIP) return;//for this mode, with just the lats is enough
      render(LONGITUDE_MODE);
    }

    //EXE-TODO:make this method private
    void render(int mode){
      int i,j,h,a,b;
      if(mode==LATITUDE_MODE){
        a=lats;
        b=longs;
      }else{
        a=longs;
        b=lats;
      }
      for(i = 1; i <= a; i++) 
      {       
       glBegin(GLMode);
         for(j = 0; j <= b; j++) 
         {   
           glNormal3f(cachedValues[mode][i-1][j][0],cachedValues[mode][i-1][j][1],cachedValues[mode][i-1][j][2]);
           glVertex3f(cachedValues[mode][i-1][j][0],cachedValues[mode][i-1][j][1],cachedValues[mode][i-1][j][2]);
           
           glNormal3f(cachedValues[mode][i][j][0],cachedValues[mode][i][j][1],cachedValues[mode][i][j][2]);                  
           glVertex3f(cachedValues[mode][i][j][0],cachedValues[mode][i][j][1],cachedValues[mode][i][j][2]);
         }
       glEnd();
      }
    }
    
    //EXE-TODO:make this method private
    void buildCachedMap(){
    //NOTE:FOR THE WATER MOVING, THIS WON'T DO....
      float u0,u1,v0,v1;
      int i, j,mode;
      float uFrom=map->getUFrom();
      float uTo=map->getUTo();
      float vFrom=map->getVFrom();
      float vTo=map->getVTo();
      mode=LATITUDE_MODE;
      for(i = 1; i <= longs; i++) 
      {             
        v0= vFrom + (((vTo-vFrom)/longs)* (i-1));
        v1= vFrom + (((vTo-vFrom)/longs)* i);

        for(j = 0; j <= lats; j++) 
        {               
          u0=uFrom + (((uTo-uFrom)/lats) * j);
          Point* point=map->get(u0,v0);
          cachedValues[mode][i-1][j][0]=(*point)[0];
          cachedValues[mode][i-1][j][1]=(*point)[1];
          cachedValues[mode][i-1][j][2]=(*point)[2];        
          
          point=map->get(u0,v1);
          cachedValues[mode][i][j][0]=(*point)[0];
          cachedValues[mode][i][j][1]=(*point)[1];
          cachedValues[mode][i][j][2]=(*point)[2];               
        }
      }

      mode=LONGITUDE_MODE;
      for(i = 1; i <= lats; i++) 
      { 
        u0= uFrom + (((uTo-uFrom)/lats)* (i-1));
        u1= uFrom + (((uTo-uFrom)/lats)* (i));             
        
        for(j = 0; j <= longs; j++) 
        {
          v0=vFrom + (((vTo-vFrom)/longs) * j);
          Point* point=map->get(u0,v0);
          cachedValues[mode][i-1][j][0]=(*point)[0];
          cachedValues[mode][i-1][j][1]=(*point)[1];
          cachedValues[mode][i-1][j][2]=(*point)[2];
          
          point=map->get(u1,v0);
          cachedValues[mode][i][j][0]=(*point)[0];
          cachedValues[mode][i][j][1]=(*point)[1];
          cachedValues[mode][i][j][2]=(*point)[2];

        }
      }
    
    }


};


#endif