#ifndef InterpolatingMapH
#define InterpolatingMapH
#include "IMap.h"

/*
This map approximates the original map passed in the constructor by using Lagrange interpolating Polygons
The map m:R2->R3 and since the polynomial p:R->R , we have to split the problem in 6.(that is , create 6 polynomials)
To do this, start by the function f:R2->R defined by
f(u,v):=Proy_x(m(u,v)) (we get just the x component)
Then we think f(u,v)=g(u)*h(v)
create polynomial P_g for g and another P_h for h
so the polynomial P_f(u,v)=P_g(u)* P_h(v)

Finally we do the analogous for the y and z component
*/
class InterpolatingMap :public IMap {  
  private:   
    IMap* map;
    std::vector<float> U;
    std::vector<float> V;
    std::vector<float> XG;
    std::vector<float> XH;
    std::vector<float> YG;
    std::vector<float> YH;
    std::vector<float> ZG;
    std::vector<float> ZH;    
    int steps=12;
    static constexpr float DELTA_STEP=0.2;
  public:
	  InterpolatingMap(IMap* map ){
        this->map=map;
        buildXY();
        /*for(int i=0;i<=steps;i++){
            std::cout << map->get(U[i],V[i])<<" vs. "<<this->get(U[i],V[i])<<std::endl;
        }*/
        //checkSeparability();
    }		

    
    void buildXY(){        
        float uFrom=map->getUFrom();
        float uTo=map->getUTo();
        float vFrom=map->getVFrom();
        float vTo=map->getVTo();
        
        float delta=getDelta(uFrom,vFrom);
        float u0=uFrom+delta;
        float v0=vFrom+delta;        

        U.reserve(steps+1);
        V.reserve(steps+1);
        XG.reserve(steps+1);
        XH.reserve(steps+1);
        YG.reserve(steps+1);
        YH.reserve(steps+1);
        ZG.reserve(steps+1);
        ZH.reserve(steps+1);
        for(int i=0;i<=steps;i++){
            float u = uFrom + (((uTo-uFrom)/steps)* i);        
            float v = vFrom + (((vTo-vFrom)/steps)* i);
            
            

            Point pG=getPG(u,u0,v0);
            Point pH=map->get(u0,v);
            U[i]=u;
            V[i]=v;
            XG[i]=pG.x;
            XH[i]=pH.x;
            YG[i]=pG.y;
            YH[i]=pH.y;
            ZG[i]=pG.z;
            ZH[i]=pH.z;
            
        }      

    }

    void checkSeparability(){
        float uFrom=map->getUFrom();
        float uTo=map->getUTo();
        float vFrom=map->getVFrom();
        float vTo=map->getVTo();
        float delta=0;
        for(int i=0;i<=steps;i++){
            delta+=DELTA_STEP;
            float u0=uFrom + delta;
            float v0=vFrom + delta;
            float error=0;
            for(int j=0;j<=steps;j++){
                float u = uFrom + (((uTo-uFrom)/steps)* j);        
                float v = vFrom + (((vTo-vFrom)/steps)* j);
                float _u0=cos(u0)*sin(v0);
                float _v0=sin(u0)*sin(v0);
                float _u=cos(u)*sin(v);
                float _v=sin(u)*sin(v);
                Point diff=prod(map->get(_u0,_v0),map->get(_u,_v)) - prod(map->get(_u,_v0),map->get(_u0,_v));
                error+=diff.norm();
            }
            std::cout << delta<<": "<<error<<std::endl;
        }
    }

    Point prod(Point p1,Point p2){
        return Point(p1.x*p2.x,p1.y*p2.y,p1.z*p2.z);
    }

    //this function gets a delta such that map(u+delta,v+delta) don't vanish (x!=0 and y!=0 and z!=0)
    float getDelta(float u,float v){        
        float delta=0;
        Point p=map->get(u,v);
        while(fabs(p.x)<DELTA_STEP || fabs(p.y)<DELTA_STEP || fabs(p.z)<DELTA_STEP ){
            delta+=DELTA_STEP/10.0;
            p=map->get(u+delta,v+delta);
        }
        return delta;
    }

    Point getPG(float u,float u0, float v0){
        Point pU0V0=map->get(u0,v0);
        Point pUV0=map->get(u,v0);
        return Point(pUV0.x/pU0V0.x,pUV0.y/pU0V0.y,pUV0.z/pU0V0.z);

    }

    //x=Px_g(u)*Px_h(v)
    //y=Py_g(u)*Py_h(v)
    //z=Pz_g(u)*Pz_h(v)
    Point get(float u,float v){        
        //return map->get(u,v);
        float x=evaluate(XG,U,u)*evaluate(XH,V,v);
        float y=evaluate(YG,U,u)*evaluate(YH,V,v);
        float z=evaluate(ZG,U,u)*evaluate(ZH,V,v);
        return Point(x,y,z);
    }

    float evaluate(std::vector<float>& Y,std::vector<float>& W,float w){//w can be u or v
        float value=0;
        for(int i=0;i<=steps;i++){ 
            float num=1;           
            float denom=1;
            for(int j=0;j<=steps;j++){
                if(i==j) continue;
                num*= (w-W[j]);
                denom*= (W[i]-W[j]);
            }
            value+=(num/denom)*Y[i];            
        }

        return value;
    }


    Point getNormal(float u,float v){
        return map->getNormal(u,v);
    }

    float getUFrom(){        
        return map->getUFrom();
    }
    float getUTo(){        
        return map->getUTo();
    }
    float getVFrom(){
        return map->getVFrom();
    } 
    float getVTo(){
        return map->getVTo();
    }

    int getLats(){
        return map->getLats();
    }
    int getLongs(){
        return map->getLongs();
    } 

};


#endif
