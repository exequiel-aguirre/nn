#ifndef BoneH
#define BoneH

#include "Ellipsoid.h"
#include "Joint.h"

class Bone: public Ellipsoid {
 private:
    Joint* jointA;
    Joint* jointB;
    static constexpr float R=0.1;
  public:
	Bone(Position&& position,Joint* jointA,Joint* jointB):Ellipsoid(std::move(position),R,getLength(jointA,jointB),R){
        this->jointA=jointA;
        this->jointB=jointB;
    }        
    
    void render(){
        this->animate();
        Ellipsoid::render();
    }

    float getLength(Joint* jointA,Joint* jointB){      
        Point pa=jointA->getPosition().getLinear();
        Point pb=jointB->getPosition().getLinear();    
        float l=(pb-pa).norm();  
        return l/2.0;
    }

    void animate(){        
        Point pa=jointA->getPosition().getLinear();
        Point pb=jointB->getPosition().getLinear();
        Point posl=(pa + pb)*0.5;

        Point p=(pb-pa).normalize();      
        Point posa=Point(acosf(p.x),acosf(p.y),acosf(p.z)) * (180.0/M_PI);//TODO:check this
        this->setPosition(posl.x,posl.y,posl.z,
        90-posa.z,0,90+posa.x);
    }
    
};


#endif
