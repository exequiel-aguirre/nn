#ifndef BezierMapH
#define BezierMapH
#include "IMap.h"


class BezierMap :public IMap {  
  private:
    IMap* map;
    //Each vector actually represents a matrix.
    //Each cell of the first matrix is a patch, which is a matrix points map(u,v)
    vector<vector<Point>> controls;
    unsigned int steps=3;
    int patches=6;
  public:
	  BezierMap(IMap* map){
        this->map=map;
        buildControlPoints();
    }

    void buildControlPoints(){
        float uFrom=map->getUFrom();
        float uTo=map->getUTo();
        float vFrom=map->getVFrom();
        float vTo=map->getVTo();

        for(int i=0;i<patches;i++){
            float patchUFrom=uFrom + ((uTo-uFrom)/patches)*i;
            float patchUTo=uFrom + ((uTo-uFrom)/patches)*(i+1);
            for(int j=0;j<patches;j++){
                float patchVFrom=vFrom + ((vTo-vFrom)/patches)*j;
                float patchVTo=vFrom + ((vTo-vFrom)/patches)*(j+1);
                controls.push_back(createControlPoints(patchUFrom,patchUTo,patchVFrom,patchVTo));
            }
        }
    }
    vector<Point> createControlPoints(float uFrom,float uTo,float vFrom,float vTo){
        vector<Point> control;
        for(unsigned int i=0;i<=steps;i++){
            float u = uFrom + (((uTo-uFrom)/steps)* i);
            for(unsigned int j=0;j<=steps;j++){
                float v = vFrom + (((vTo-vFrom)/steps)* j);
                control.push_back(this->map->get(u,v));
            }
        }
        return control;
    }

    Point get(float u,float v){
        Point value;
        vector<Point>& control = getControlPoints(u,v);
        for(unsigned int i=0;i<=steps;i++){
            for(unsigned int j=0;j<=steps;j++){
                value=value+ B(u,steps,i) * B(v,steps,j) * control[(i*(steps+1)) + j];
            }
        }
        return value;
    }

    vector<Point>& getControlPoints(float& u,float& v){
        float uFrom=getUFrom();
        float uTo=getUTo();
        float vFrom=getVFrom();
        float vTo=getVTo();
        //TODO:avoid these next 4 lines.
        //the IMap:getTangent is calling the map with values u,v out of the domain
        u=std::max(u,getUFrom());
        u=std::min(u,getUTo());
        v=std::max(v,getVFrom());
        v=std::min(v,getVTo());
        
        for(int i=0;i<patches;i++){
            float patchUFrom=uFrom + ((uTo-uFrom)/patches)*i;
            float patchUTo=uFrom + ((uTo-uFrom)/patches)*(i+1);
            for(int j=0;j<patches;j++){
                float patchVFrom=vFrom + ((vTo-vFrom)/patches)*j;
                float patchVTo=vFrom + ((vTo-vFrom)/patches)*(j+1);
                
                if( (patchUFrom<=u && u<=patchUTo) && (patchVFrom<=v && v<=patchVTo) ){
                    u=changeDomain(u,patchUFrom,patchUTo);
                    v=changeDomain(v,patchVFrom,patchVTo);
                    return controls[(i*patches) + j];
                }
            }
        }        

        std::cout << "out of domain!!! ("<<u<<", "<<v<<")\n";exit(0);
        return controls[0];
    }

    Point getNormal(float theta,float phi){
        theta*=2*M_PI;
        phi*=M_PI;
        float x_theta=-sin(theta)*sin(phi);
        float y_theta=cos(theta)*sin(phi);
        float z_theta=0.0f;
        Point p1= Point(x_theta,y_theta,z_theta);
        
        float x_phi=cos(theta)*cos(phi);
        float y_phi=sin(theta)*cos(phi);
        float z_phi=-sin(phi);
        Point p2= Point(x_phi,y_phi,z_phi);

        return (p2^p1).normalize();
    }

    //f(w):[a,b]->[0,1]->[]
    float changeDomain(float w,float a,float b){
        return (w-a)/(b-a);
    }

    float B(float w,unsigned int n,unsigned int i){
        return binomialCoefficient(n,i) * pow(w,i) * pow(1.0f-w,n-i);
    }


    unsigned int binomialCoefficient(unsigned int n,unsigned int i){
        return factorial(n)/(factorial(i) * factorial(n-i));
    }
    unsigned int factorial(unsigned int n){
        if(n==0) return 1;
        return n*factorial(n-1);
    }

    float getUFrom(){        
        return 0+EPSILON;
    }
    float getUTo(){        
        return 1.0-EPSILON;
    }
    float getVFrom(){
        return 0+EPSILON;
    } 
    float getVTo(){
        return 1.0-EPSILON;
    }

    int getLats(){
        return 12;
    }
    int getLongs(){
        return 12;
    }     

};


#endif
