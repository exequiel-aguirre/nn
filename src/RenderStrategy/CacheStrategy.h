#ifndef CacheStrategyH
#define CacheStrategyH
#include "IRenderStrategy.h"


class CacheStrategy :public IRenderStrategy {  
  private:        
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
      int i,j;
      for(i = 1; i <= longs; i++) 
      {       
       glBegin(GLMode);
         for(j = 0; j <= lats; j++) 
         {   
           glNormal3f(cachedValues[0][i-1][j][0],cachedValues[0][i-1][j][1],cachedValues[0][i-1][j][2]);
           glVertex3f(cachedValues[0][i-1][j][0],cachedValues[0][i-1][j][1],cachedValues[0][i-1][j][2]);
           
           glNormal3f(cachedValues[0][i][j][0],cachedValues[0][i][j][1],cachedValues[0][i][j][2]);                  
           glVertex3f(cachedValues[0][i][j][0],cachedValues[0][i][j][1],cachedValues[0][i][j][2]);
         }
       glEnd();
      }


      for(i = 1; i < lats; i++) 
      {         
       glBegin(GLMode);
         for(j = 0; j <= longs; j++) 
         { 
           glNormal3f(cachedValues[1][i-1][j][0],cachedValues[1][i-1][j][1],cachedValues[1][i-1][j][2]);
           glVertex3f(cachedValues[1][i-1][j][0],cachedValues[1][i-1][j][1],cachedValues[1][i-1][j][2]);
           
           glNormal3f(cachedValues[1][i][j][0],cachedValues[1][i][j][1],cachedValues[1][i][j][2]);                  
           glVertex3f(cachedValues[1][i][j][0],cachedValues[1][i][j][1],cachedValues[1][i][j][2]);
         }
       glEnd();
      }
    }


    void buildCachedMap(){
    //NOTE:FOR THE WATER MOVING, THIS WON'T DO....
      float u0,u1,v0,v1;
      int i, j;
      float uFrom=map->getUFrom();
      float uTo=map->getUTo();
      float vFrom=map->getVFrom();
      float vTo=map->getVTo();
      for(i = 1; i <= longs; i++) 
      {             
        v0= vFrom + (((vTo-vFrom)/longs)* (i-1));
        v1= vFrom + (((vTo-vFrom)/longs)* i);

        for(j = 0; j <= lats; j++) 
        {               
          u0=uFrom + (((uTo-uFrom)/lats) * j);
          cachedValues[0][i-1][j][0]=map->getX(u0,v0);
          cachedValues[0][i-1][j][1]=map->getY(u0,v0);
          cachedValues[0][i-1][j][2]=map->getZ(u0,v0);        

          cachedValues[0][i][j][0]=map->getX(u0,v1);
          cachedValues[0][i][j][1]=map->getY(u0,v1);
          cachedValues[0][i][j][2]=map->getZ(u0,v1);               
        }
      }

      for(i = 1; i < lats; i++) 
      { 
        u0= uFrom + (((uTo-uFrom)/lats)* (i-1));
        u1= uFrom + (((uTo-uFrom)/lats)* (i));             
        
        for(j = 0; j <= longs; j++) 
        {
          v0=vFrom + (((vTo-vFrom)/longs) * j);
          cachedValues[1][i-1][j][0]=map->getX(u0,v0);
          cachedValues[1][i-1][j][1]=map->getY(u0,v0);
          cachedValues[1][i-1][j][2]=map->getZ(u0,v0);

          cachedValues[1][i][j][0]=map->getX(u1,v0);
          cachedValues[1][i][j][1]=map->getY(u1,v0);
          cachedValues[1][i][j][2]=map->getZ(u1,v0);

        }
      }
    
    }


};


#endif