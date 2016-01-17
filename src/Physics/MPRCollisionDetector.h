/*
This is a modified implementation of the MPR algorithm wrote by Gary Snethen,
the original code can be found at http://xenocollide.com
*/
#ifndef MPRCollisionDetectorH
#define MPRCollisionDetectorH
#include "../DataStructure/Boundary.h"
#include "../DataStructure/Matrix.h"

class MPRCollisionDetector{  
  public:
    MPRCollisionDetector(){}
    virtual ~MPRCollisionDetector(){}
    
    bool detect(Boundary& b1,Boundary& b2){
        Point& min1=b1.getEnclosingBox().getDiagonalMin();
        Point& max1=b1.getEnclosingBox().getDiagonalMax();
        Point& min2=b2.getEnclosingBox().getDiagonalMin();
        Point& max2=b2.getEnclosingBox().getDiagonalMax();
        //this is the intersection segment length (how bad the crash was...)
        float islx=std::min(max1.x,max2.x)-std::max(min1.x,min2.x);
        float isly=std::min(max1.y,max2.y)-std::max(min1.y,min2.y);
        float islz=std::min(max1.z,max2.z)-std::max(min1.z,min2.z);
       
        if( (islx >= 0) && (isly >= 0) && (islz >= 0) ) {

            Point impactNormal;
            Point impactPoint;
            float d=0.0f;
            if(!collideAndFindPoint(b1,b2,impactNormal,impactPoint,d)) return false;

            b1.getCollisionStatus().setImpactPoint(impactPoint).setImpactNormal(impactNormal).setDistance(d);
            b2.getCollisionStatus().setImpactPoint(impactPoint).setImpactNormal(-impactNormal).setDistance(d);

            Point volume=Point(islx,isly,islz);
            b1.getCollisionStatus().set(volume,true);
            b2.getCollisionStatus().set(volume,true);

            return true;
        }else{
            return false;
        }
    }


    bool collideAndFindPoint(Boundary& b1,Boundary& b2,Point& impactNormal,Point& impactPoint,float& penetration){
        static float kCollideEpsilon = 1e-3f;

        Point v01=b1.getEnclosingBox().getCenter();
        Point v02=b2.getEnclosingBox().getCenter();
        Point v0=v02-v01;

        if(v0.isZero()) v0=Point(0.0001,0,0);//special case

        Point n=-v0;
        Point v11=getSupportPoint(b1,-n);
        Point v12=getSupportPoint(b2,n);
        Point v1=v12-v11;

        if(v1*n <=0)
        {
            impactNormal=n;
            return false;
        }

       n=v1^v0;
       if(n.isZero())
       {
            n=v1-v0;
            n.normalize();
            impactNormal=n;
            impactPoint=(v11+v12)*0.5;
            penetration= (v12-v11)*n;
            return true;
       }

        Point v21=getSupportPoint(b1,-n);
        Point v22=getSupportPoint(b2,n);
        Point v2=v22-v21;
        if(v2*n <=0)
        {
            impactNormal=n;
            return false;
        }

        n=(v1-v0)^(v2-v0);
        float dist= n*v0;

        if(n.isZero()) exit(4);

        if(dist>0)
        {
            std::swap(v1,v2);
            std::swap(v11,v21);
            std::swap(v12,v22);
            n=-n;
        }


        //Phase 1: Identify the portal
        while(true)
        {
            Point v31=getSupportPoint(b1,-n);
            Point v32=getSupportPoint(b2,n);
            Point v3=v32-v31;

            if(v3*n<=0)
            {
                impactNormal=n;
                return false;                
            }

            if((v1^v3) * v0 <0)
            {
                v2=v3;
                v21=v31;
                v22=v32;
                n=(v1-v0)^(v3-v0);
                continue;
            }

            if((v3^v2) * v0 <0)
            {
                v1=v3;
                v11=v31;
                v12=v32;
                n=(v3-v0)^(v2-v0);
                continue;
            }

            bool hit=false;


            //Phase 2: Portal refinement
            while(true)
            {
                n=(v2-v1) ^ (v3-v1);

                if(n.isZero())
                {
                    return true;
                }

                n.normalize();

                float d=n*v1;

                if(d>=0 && !hit)//TODO!:in the original code it's 0 instead of -0.5. This was just to fix a bug, but I need to find a better way
                {
                    impactNormal=n;

                    //Calculate the barycentric coordinates of the origin
                    float ba0=(v1^v2) * v3;
                    float ba1=(v3^v2) * v0;
                    float ba2=(v0^v1) * v3;
                    float ba3=(v2^v1) * v0;
                    float sum=ba0+ba1+ba2+ba3;
                    if(sum<=0)
                    {
                        ba0=0;
                        ba1=(v2^v3) * n;
                        ba2=(v3^v1) * n;
                        ba3=(v1^v2) * n;
                        sum=ba1+ba2+ba3;
                    }
                    float inv=1.0/sum;
                    impactPoint=( (ba0*v01 + ba1*v11 + ba2*v21 + ba3*v31)+(ba0*v02 + ba1*v12 + ba2*v22+ ba3*v32) ) *inv * 0.5;


                    //hit!!!
                    hit=true;
                }


                Point v41=getSupportPoint(b1,-n);
                Point v42=getSupportPoint(b2,n);
                Point v4=v42-v41;

                float delta=(v4-v3) * n;
                float separation=-(v4*n);

                if(delta<=kCollideEpsilon || separation>=0)
                {
                    impactNormal=n;
                    penetration=separation;
                    return hit;
                }

                float d1=(v4^v1) * v0;
                float d2=(v4^v2) * v0;
                float d3=(v4^v3) * v0;
                    
                if(d1<0)
                {
                    if(d2<0)
                    {//-v1
                        v1 = v4;
                        v11 = v41;
                        v12 = v42;
                    }
                    else
                    {//-v3
                        v3 = v4;
                        v31 = v41;
                        v32 = v42;
                    }
                }
                else
                {
                    if(d3<0)
                    {//-v2
                        v2 = v4;
                        v21 = v41;
                        v22 = v42;
                    }
                    else
                    {//-v1
                        v1 = v4;
                        v11 = v41;
                        v12 = v42;

                    }
                }
            }

        }

    //imposible case, but to avoid warning
    return false;
    }

    
    //ex-getFarthestAlong
    //TODO:check if we should modify the normal in world coordinates
    Point getSupportPoint(Boundary& b,Point v){
        //- rotation
        Matrix& rotationInverseMatrix=b.getReducedPolygon().getRotationInverseMatrix();
        v=rotationInverseMatrix*v;

        Point max=b.getReducedPolygon().getFarthestAlong(v);
        
        Matrix& modelMatrix=b.getReducedPolygon().getModelMatrix();
        return modelMatrix*max;
    }
    

};
#endif
