#ifndef ConeMapH
#define ConeMapH
#include "IMap.h"

//This is juast an inverted cone
class ConeMap :public IMap {  
  private:
    float r;
    float h;
    int lats=12;
    int longs=12;
  public:
	  ConeMap(float r,float h,int lats,int longs){
        this->r=r;
        this->h=h;
        this->lats=lats;
        this->longs=longs;
      }

       ConeMap(float r,float h):ConeMap(r,h,12,12){}

            
    Point get(float u,float theta){
        float x=u* cos(theta);
        float y=h-u*(h/r);
        float z=u*sin(theta);
        return Point(x,y,z);
    }

    Point getNormal(float u,float theta){
        float x_u=cos(theta);
        float y_u=-(h/r);
        float z_u=sin(theta);
        Point p1= Point(x_u,y_u,z_u);
        
        float x_theta=u* -sin(theta);
        float y_theta=0.0f;
        float z_theta=u*cos(theta);
        Point p2=Point(x_theta,y_theta,z_theta);

        return (p2^p1).normalize();
    }
    

    std::function<Point(Point)> getSupportFunction(){
        float r=this->r;
        float h=this->h;
        return ( [r,h](Point v){
          Point sp=Point(0,h,0);

          Point d=Point(v.x,0,v.z);//disc
          Point sd=r*d* (d.isZero()?1.0:(1.0/d.norm()));//TODO:check this if....
          if(sp*v > sd*v){
            return sp;
          }
          else{
            return sd;
          }
        });
    }

    float getUFrom(){        
        return 0+EPSILON;
    }
    float getUTo(){        
        return r-EPSILON;
    }
    float getVFrom(){
        return 0+EPSILON;
    } 
    float getVTo(){
        return 2*M_PI-EPSILON;
    } 

    int getLats(){
        return lats;
    }
    int getLongs(){
        return longs;
    } 

};


#endif
