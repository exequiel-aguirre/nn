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
        Point posa=getAngularPosition(pb-pa);

        this->setPosition(posl.x,posl.y,posl.z,
                            posa.x,posa.y,posa.z);
    }

    /*
    We create an orthonormal basis {u1,u2,u3} with u1=(pb-pa)/||pb-pa|| 
    Then create a linear transformation T that takes (0,1,0) to u1.
    Note that (0,1,0) is the initial position of the bone, i.e. ( R,getLength(jointA,jointB),R )
    So we have T:<e1,e2,e3> -> <u3,u1,u2>
    a) T is orthonormal by construction
    b) Because of a, det(T) is either 1 or -1, but arranging u3 and u2 in the right order, we have that det(T)=1. (*)
    With a) and b) => T is a rotation matrix. (So it makes sense to extract euler angles from it)

    (*) det(T)=u3 (u1^u2)=u3 u3 = ||u3||>0 and (because of 1) ) => det(T)=1
    */
    Point getAngularPosition(Point pba){
        Point u1=pba.normalize();
        Point u2=u1^Point(0,1,0);
        if((u2*u2)< 0.004){
            u2=u1^Point(0,0,1);
        }
        u2.normalize();
        Point u3=(u1^u2).normalize();

        float r[16]={
            u3.x , u1.x , u2.x , 0,
            u3.y , u1.y , u2.y , 0 ,
            u3.z , u1.z , u2.z , 0 ,
            0 , 0 , 0 , 1 };
        
        vector<float> eulerAngles=Matrix(r).getEulerAngles();

        return Point(eulerAngles[0],eulerAngles[1],eulerAngles[2]);
    }
    
};


#endif
