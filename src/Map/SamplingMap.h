#ifndef SamplingMapH
#define SamplingMapH
#include "IMap.h"


class SamplingMap :public IMap {  
  private:   
    std::vector<Point> vertices;
  public:
	  SamplingMap(std::vector<Point> moVertices ){
        this->vertices=moVertices;
    }		

    
    Point get(float theta,float phi){
        float x=cos(theta)*sin(phi);
        float y=sin(theta)*sin(phi);
        float z=cos(phi);        

        return getFarthestAlong(Point(x,y,z));
        
    }

    Point getNormal(float theta,float phi){
         float x=cos(theta)*sin(phi);
        float y=sin(theta)*sin(phi);
        float z=cos(phi);
        return Point(x,y,z);
    }

    Point getFarthestAlong(const Point& v){
      Point max=vertices[0];
      float maxDot=max*v;
      for(Point& p:vertices){
        float pDot=p*v;
        if(pDot > maxDot){
          max=p;
          maxDot=pDot;
        }
      }
      return max;
    }



    float getUFrom(){        
        return 0;
    }
    float getUTo(){        
        return (2*M_PI);
    }
    float getVFrom(){
        return 0+EPSILON;
    } 
    float getVTo(){
        return M_PI -EPSILON;
    }

    int getLats(){
        return 8;
    }
    int getLongs(){
        return 8;
    }

};


#endif
