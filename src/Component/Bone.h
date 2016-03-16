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

        //Point p=(pb-pa).normalize();      
        //this->setPosition(posl.x,posl.y,posl.z);
        this->position.set(posl.x,posl.y,posl.z);
        customUpdateModelMatrix(pb-pa,posl);
        this->calculateBoundary();
    }
    /*
    We create an orthonormal basis {u1,u2,u3} with u1=(pb-pa)/||pb-pa|| 
    Then create a linear transformation that takes (0,1,0) to u1.
    Note that (0,1,0) is the initial position of the bone, i.e. ( R,getLength(jointA,jointB),R )
    u2 and u3 order in T was picked at random.
    This 3x3 submatrix give the bone the correct orientation.Finally we add the translation
    */
    void customUpdateModelMatrix(Point pba,Point posl){
        Point u1=pba.normalize();
        Point u2=u1^Point(0,1,0);
        if((u2*u2)< 0.004){
            u2=u1^Point(0,0,1);
        }
        u2.normalize();
        Point u3=(u1^u2).normalize();

        float r[16]={
            u2.x , u1.x , u3.x , posl.x ,
            u2.y , u1.y , u3.y , posl.y ,
            u2.z , u1.z , u3.z , posl.z ,
            0 , 0 , 0 , 1 };
        
        std::copy(r, r+16, modelMatrix.rawMatrix);        
    }
    
};


#endif
