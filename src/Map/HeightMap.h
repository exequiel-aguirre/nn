#ifndef HeightMapH
#define HeightMapH
#include "IMap.h"

class HeightMap :public IMap {
  private:
    float w;
    float h;
    int lats;
    int longs;
    //TODO:make it an float vector?
    vector<Uint8> pixels;
    int imageWidth;
    int imageHeight;
    const Uint8 MAX_HEIGHT=300;
    const float FACTOR=MAX_HEIGHT/(pow(2,7));
    const Uint8 SEA_LEVEL=pow(2,7);
  public:
	HeightMap(float w,float h,int lats,int longs,vector<Uint8> pixels,int imageWidth,int imageHeight){
        this->w=w;
        this->h=h;
        this->lats=lats;
        this->longs=longs;
        this->pixels=pixels;
        this->imageWidth=imageWidth;
        this->imageHeight=imageHeight;
        this->repeat=true;
      }    

    virtual ~HeightMap(){}

   Point get(float u,float v){
        //Move the domain to [0,w]x[x,h] and then scale it to [0,imageWidth-1]x[0,imageHeight-1]
        int x=(int)((u + this->w/2) * (this->imageWidth-1)/this->w);
        int z=(int)((v + this->h/2) * (this->imageHeight-1)/this->h);
        float y=(pixels[ ( z * this->imageWidth ) + x ] - SEA_LEVEL)*FACTOR;

        return Point(u,y,v);
    }
 
    
    Point getNormal(float u,float v){        
        float deltaU=w/lats;
        Point p1=(this->get(u+deltaU,v) - this->get(u,v))*(1/deltaU);        

        float deltaV=h/longs;
        Point p2=(this->get(u,v+deltaV) - this->get(u,v))*(1/deltaV);

        return (p2^p1).normalize();
    }

    float getUFrom(){        
        return -w/2;
    }
    float getUTo(){        
        return w/2;
    }
    float getVFrom(){
        return -h/2;
    } 
    float getVTo(){
        return h/2;
    } 

    int getLats(){
        return lats;
    }
    int getLongs(){
        return longs;
    } 

};


#endif
