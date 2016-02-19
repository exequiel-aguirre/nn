#ifndef SamplingMapH
#define SamplingMapH
#include "IMap.h"


class SamplingMap :public IMap {  
  private:   
    std::vector<Point> vertices;
    std::function<Point(Point)> supportFunction;
  public:
	  SamplingMap(std::vector<Point> moVertices ){
        this->vertices=moVertices;
        this->supportFunction=getSupportFunction();
    }		

    
    Point get(float theta,float phi){
        float x=cos(theta)*sin(phi);
        float y=sin(theta)*sin(phi);
        float z=cos(phi);        

        return supportFunction(Point(x,y,z));
        
    }

    Point getNormal(float theta,float phi){
         float x=cos(theta)*sin(phi);
        float y=sin(theta)*sin(phi);
        float z=cos(phi);
        return Point(x,y,z);
    }

    std::function<Point(Point)> getSupportFunction(){
      std::vector<Point> vertices=this->vertices;
        return ( [vertices](Point v){
          auto max=std::max_element(vertices.begin(),vertices.end(),
          [&v](Point p1, Point p2) {
                return (p1-p2)*v < 0;
            });
          return max[0];
        });
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
