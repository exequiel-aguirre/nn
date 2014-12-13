#ifndef CollisionDetectorH
#define CollisionDetectorH
#include "../Component/Component.h"
#include "../Utils/Utils.h"
#include <typeinfo>


class CollisionDetector{
  private:
    constexpr static float epsilon=0.2f;
    //TODO:this is component's property
    constexpr static float e=0.88f;//Coefficient of restitution,1 is perfectly elastic,0 is perfectly plastic
  public:
    CollisionDetector(){}
    virtual ~CollisionDetector(){}
    
    static bool detect(Component* c1,Component* c2){
        if((c1->getBoundaryMin()==NULL)||(c1->getBoundaryMax()==NULL) ||
            (c2->getBoundaryMin()==NULL)||(c2->getBoundaryMax()==NULL)) return false;    	
    	
        Point* min1=c1->getBoundaryMin();
        Point* max1=c1->getBoundaryMax();
        Point* min2=c2->getBoundaryMin();
        Point* max2=c2->getBoundaryMax();
        //this is the intersection segment length (how bad the crash was...)
        float islx=std::min(max1->x,max2->x)-std::max(min1->x,min2->x);
        float isly=std::min(max1->y,max2->y)-std::max(min1->y,min2->y);
        float islz=std::min(max1->z,max2->z)-std::max(min1->z,min2->z);
       
        if( (islx >= 0) && (isly >= 0) && (islz >= 0) ) {
            
            if(getSeparation(c1,c2) > epsilon) return false;

            //v1 and v2 final velocity, v1_i and v2_i initial velocity
            float v1,v2,v1_i,v2_i;
            float m1=c1->getMass();
            float m2=c2->getMass();
            //TODO:same thing for x,y and z. Put all these in a method
            //collision on X 
            //check if the objects crashed into each other or just scratch the surface
            if(isly*islz>0){//the isly*islz is the area of the contact surface defined by the x-axis as normal
                v1_i=c1->getVelocity()->getX();
                v2_i=c2->getVelocity()->getX();            
                v1=((m1*v1_i) + (m2*v2_i) + (m2 * e *(v2_i-v1_i)))/(m1+m2);
                v2=((m1*v1_i) + (m2*v2_i) + (m1 * e *(v1_i-v2_i)))/(m1+m2);
                c1->getVelocity()->setX(v1);
                c2->getVelocity()->setX(v2);
            }

            //collision on Y
            if(islx*islz>0){
                v1_i=c1->getVelocity()->getY();
                v2_i=c2->getVelocity()->getY();            
                v1=((m1*v1_i) + (m2*v2_i) + (m2 * e *(v2_i-v1_i)))/(m1+m2);
                v2=((m1*v1_i) + (m2*v2_i) + (m1 * e *(v1_i-v2_i)))/(m1+m2);
                c1->getVelocity()->setY(v1);
                c2->getVelocity()->setY(v2);
            }
            //collision on Z
            if(islx*isly>0){
                v1_i=c1->getVelocity()->getZ();
                v2_i=c2->getVelocity()->getZ();            
                v1=((m1*v1_i) + (m2*v2_i) + (m2 * e *(v2_i-v1_i)))/(m1+m2);
                v2=((m1*v1_i) + (m2*v2_i) + (m1 * e *(v1_i-v2_i)))/(m1+m2);
                c1->getVelocity()->setZ(v1);
                c2->getVelocity()->setZ(v2);
            }

                       
            // std::cout << typeid(*c1).name()<<" collided with a "<< typeid(*c2).name()<<": "<<islx<<", "<<isly<<", "<<islz<<"\n";
            /*std::string str1(typeid(*c1).name());
            std::string str2(typeid(*c2).name());
            if((str1=="6Sphere") && (str2=="6Ground") && c1->getCollisionStatus()->getYMax()){
                std::cout << typeid(*c1).name()<<" collided with a "<< typeid(*c2).name()<<'\n';
                std::cout << v1 <<"," <<v2<<"\n";
            }*/
            
            
                
            c1->getCollisionStatus()->set(
                min1->x <= min2->x,
                max1->x >= max2->x,
                min1->y <= min2->y,
                max1->y >= max2->y,
                min1->z <= min2->z,
                max1->z >= max2->z
                );
            c2->getCollisionStatus()->set(
                min2->z <= min1->z,
                max2->z >= max1->z,
                min2->y <= min1->y,
                max2->y >= max1->y,
                min2->z <= min1->z,
                max2->z >= max1->z
                );

            return true;
    	}else{
            return false;
        }
    }

    //TODO:find a better name:We cannot call it distance, since separation(a,b)!=separation(b,a)
    static float getSeparation(Component* c1,Component* c2){

        Point* p;
        vector<Point*>* vertices1=c1->getModelObject()->getModelObjectVO()->getPositionedIndexedVertices();
        vector<Point*>::iterator it1;

        vector<std::pair<Point*,Point*>>* trianglePlanes2=c2->getModelObject()->getModelObjectVO()->getPositionedTrianglePlanes();
        vector<std::pair<Point*,Point*>>::iterator it2;
        float d=1000000;
        for(it1=vertices1->begin();it1!=vertices1->end();it1++){
            //a point of c1
            p=*it1;
            for(it2=trianglePlanes2->begin();it2!=trianglePlanes2->end();it2++){
                //get the distance from p to the plane of each triangle of c2
                Point* x0=(*it2).first;
                Point* n=(*it2).second;
                float d1=distance(p,x0,n);
                if(d1<d) d=d1;
            }
        }

        //std::cout <<d<<"\n";
        //std::cout << typeid(*c1).name()<<" collided with a "<< typeid(*c2).name()<<"\n";
        //std::cout <<p<<v1<<v2<<v3<< "\n";
        return d;
    }

    static float distance(Point* p,Point* x0,Point* n){
        //n.(p-x0)
        return fabs((n->x *(p->x-x0->x))+(n->y *(p->y-x0->y))+(n->z *(p->z-x0->z)));
    }
};
#endif
