#ifndef CollisionContainerH
#define CollisionContainerH

#include "../Component/Container.h"
#include "../Component/Sphere.h"
#include "../Component/Ellipsoid.h"
#include "../Component/Torus.h"
#include "../Component/Plane.h"
#include "../Component/Mountain.h"
#include "../Component/Cloud.h"
#include "../Component/Tree.h"
#include "../Component/Water.h"
#include "../Component/Animation.h"
#include "../Component/Skeleton.h"
#include "../Component/Box.h"
#include "../Component/Hut.h"
#include "../Component/Mill.h"
#include "../Component/Ground.h"
#include "../Component/Grass.h"
#include "../Component/Terrain.h"
#include "../Component/FirePlace.h"
#include "../Component/Bridge.h"
#include "../Component/Building.h"
#include "../Component/Camera.h"
#include "../Component/InteractiveCamera.h"
#include "../Effect/Fog.h"
#include "../Effect/Reflection.h"
#include "../Effect/Shadow.h"
#include "../Component/Light.h"
#include "../Component/Physics.h"
#include "../Physics/Constraint/DistanceConstraint.h"
#include "../Component/Stats.h"
#include "../Behavior/MotionBehavior.h"
#include "../Map/SamplingMap.h"
#include "../Map/BezierMap.h"
#include "../Map/CuboidMap.h"




class CollisionContainer:public Container{
  private:
	const float GROUND_LEVEL=0.0;
  public:
    CollisionContainer(Position&& position):Container(position){
            test14();

			add(new InteractiveCamera(Position(0.0f,5.0f,10.0f)));
            Light* myLight=new Light(Position(180.0,98.0,172.0,28.0,-38.0,0.0));
			add(myLight);
			add(new Physics());
			add(new Stats());
			add(new Fog());
            add(new Shadow(myLight));
    }

    void test1(){//+0.1
        Component* sphere=(new Sphere(Position(-5,1,0),0.5f))->add(new MotionBehavior());
        sphere->setVelocity(1,0,0);
        add(sphere);
        add( (new Model(Position(5,0,0,0,270,0),"3DModel/monkey.obj","img/default.bmp"))->add(new MotionBehavior()) );
    }

    void test2(){//+1.0
        Component* sphere=(new Sphere(Position(-10,2,2.5),1.5f))->add(new MotionBehavior());
        sphere->setVelocity(15,0,0);
        add(sphere);
        add( (new Plane(Position(0,0,0,45.0,0,90.0),5,5,"img/box.bmp"))->add(new MotionBehavior()) );
    }

    void test3(){
        Component* sphere=(new Sphere(Position(-5,2,2.0),1.0f))->add(new MotionBehavior());
        sphere->setVelocity(15,0,0);
        add(sphere);
        add( (new Box(Position(5,0,0,0.0,0,0.0),5,5,5,"img/box.bmp"))->add(new MotionBehavior()) );
    }

     void test4(){
        Component* sphere=(new Sphere(Position(-5,2,10),1.5f))->add(new MotionBehavior());
        sphere->setVelocity(5,0,0);
        add(sphere);
        add( (new Plane(Position(5,0,0,45.0,0,90.0),5,30,"img/box.bmp"))->add(new MotionBehavior()) );
    }

     void test5(){
        add(new Ground(Position(0.0f,GROUND_LEVEL,0.0f),300,300));
        add( (new Model(Position(5,10,0,0,270,0),"3DModel/monkey.obj","img/default.bmp"))->add(new MotionBehavior()) );
        add( (new Box(Position(0,20,0,0.0,0,60.0),5,5,5,"img/box.bmp"))->add(new MotionBehavior()) );
    }
    void test6(){
        add( (new Cylinder(Position(0,-30,-120,90,0,0),2.0,50.0,"img/default.bmp"))/*->add(new MotionBehavior())*/ );
        add( (new Box(Position(0,-25,-100),20,2,5,"img/box.bmp"))->add(new MotionBehavior()) );
    }
    void test7(){
        add(new Ground(Position(0.0f, GROUND_LEVEL, 0.0f, 2.0, 0.0, 2.0),300,300));
        //add( (new Box(Position(5,3,-5,-30,00,0),2,2,5,"img/box.bmp"))->add(new MotionBehavior()) );//working.
        add( (new Box(Position(5,3,-5,-30,90,0),2,2,5,"img/box.bmp"))->add(new MotionBehavior()) );//not working

        //add( (new Box(Position(5,3,-5,-0,0,0),2,2,5,"img/box.bmp"))->add(new MotionBehavior()) );
        //add( (new Box(Position(5,10,-5),1,1,1,"img/box.bmp"))->add(new MotionBehavior()) );
        //add((new Sphere(Position(-5,15,10),1.5f))->add(new MotionBehavior()));
    }

    void test8(){
        float z1=5.0;
        float z2=5.0000001;
        add(new Box(Position(0.0f, -1, 0.0f),300,2,300,"img/ground.bmp"));
        add( (new Box(Position(5,5,-z1),2,2,2,"img/box.bmp"))->add(new MotionBehavior()) );
        add( (new Box(Position(5,10,-z2),2,2,2,"img/box.bmp"))->add(new MotionBehavior()) );
        add( (new Box(Position(5,15,-z1),2,2,2,"img/box.bmp"))->add(new MotionBehavior()) );
        add( (new Box(Position(5,20,-z2),2,2,2,"img/box.bmp"))->add(new MotionBehavior()) );
        add( (new Box(Position(5,25,-z1),2,2,2,"img/box.bmp"))->add(new MotionBehavior()) );
        add( (new Box(Position(5,30,-z2),2,2,2,"img/box.bmp"))->add(new MotionBehavior()) );
        add( (new Box(Position(5,35,-z1),2,2,2,"img/box.bmp"))->add(new MotionBehavior()) );
        add( (new Box(Position(5,40,-z2),2,2,2,"img/box.bmp"))->add(new MotionBehavior()) );
        add( (new Box(Position(5,45,-z1),2,2,2,"img/box.bmp"))->add(new MotionBehavior()) );
        add( (new Box(Position(5,50,-z2),2,2,2,"img/box.bmp"))->add(new MotionBehavior()) );
        /*add( (new Box(Position(5,55,-z1),2,2,2,"img/box.bmp"))->add(new MotionBehavior()) );
        add( (new Box(Position(5,60,-z2),2,2,2,"img/box.bmp"))->add(new MotionBehavior()) );*/
        //add( (new Box(Position(5,10,-5),1,1,1,"img/box.bmp"))->add(new MotionBehavior()) );
        //add((new Sphere(Position(-5,15,10),1.5f))->add(new MotionBehavior()));
    }
     void test9(){
        add(new Box(Position(0.1f, -1, 0.1f),300,2,300,"img/ground.bmp"));
        add( (new Box(Position(0,5,0,0,-15,-90),2,2,2,"img/box.bmp"))->add(new MotionBehavior()) );
        //add( (new Box(Position(0,5,0,0,0,0),2,2,2,"img/box.bmp"))->add(new MotionBehavior()) );
    }
    void test10(){
        add(new Ground(Position(0.0f, -1, 0.0f),300,300));
        add( (new Box(Position(5,5,-5,45,45,45),2,2,5,"img/box.bmp"))->add(new MotionBehavior()) );
        //add((new Ellipsoid(Position(5,5,-5),0.5f,1.0,0.5))->add(new MotionBehavior()));
        add( (new Surface(Position(-5.0f,3.0f,-5.0f),CuboidMap(2,2,2),"img/default.bmp"))->add(new MotionBehavior()) );
    }
    //Elasticity must be set to 1.0 to work (more or less) as expected
    void test11(){
        add(new Ground(Position(0.0f, GROUND_LEVEL, 0.0f, 2.0, 0.0, 2.0),300,300));
        float bw=0.5;
        for(int i=0;i<5;i++){
            float offsetX=(i==4)?3:0;
            float offsetY=(i==4)?1:0;
            Box* box=new Box(Position(i*(bw), 8, 0.0f),bw,bw,bw,"img/box.bmp");
            Sphere* sphere=new Sphere(Position(i*bw+offsetX,3+offsetY,0),bw*0.5);
            sphere->add(new MotionBehavior())->setRotates(false);
            add(box);
            add(sphere);//x** 2 + (5-y)**2=25
            //PhysicsManager::getInstance().add(new DistanceConstraint(sphere,box));
            PhysicsManager::getInstance().add(new DistanceConstraint(sphere,box,Point(i*bw+offsetX,3+offsetY,0),Point(i*(bw), 8, -0.2f)));//The -0.2 and 0.2 is to avoid
            PhysicsManager::getInstance().add(new DistanceConstraint(sphere,box,Point(i*bw+offsetX,3+offsetY,0),Point(i*(bw), 8,  0.2f)));//spheres movement along z
        }
    }

    void test12(){
        add(new Ground(Position(0.0f, GROUND_LEVEL, 0.0f, 2.0, 0.0, 2.0),300,300));

        Model* myModel=new Model(Position(-5.0f,3,-5),"3DModel/human.obj","img/default.bmp");
        add(myModel);
        //add(new Surface(Position(0.0f,3.0f,-5.0f),SamplingMap(myModel->getBoundary().getReducedPolygon().getVertices()),"img/default.bmp"));
        //add(new Surface(Position(5.0f,3.0f,-5.0f),BezierMap(new SamplingMap(myModel->getBoundary().getReducedPolygon().getVertices())),"img/default.bmp") );
    }
    //ragdoll
    void test13(){
        add(new Ground(Position(0.0f, GROUND_LEVEL, 0.0f, 2.0, 0.0, 2.0),300,300));
        float ba=1.5;
        float bb=0.5;
        float bc=0.5;
        //body
        Point bp=Point(-5,7,-10);
        Ellipsoid* body=(new Ellipsoid(Position(bp.x,bp.y,bp.z,0,0,90),ba,bb,bc));
        add(body->add(new MotionBehavior()));
        //head
        float ha=ba/3.0;
        float hb=bb/3.0;
        float hc=bc/3.0;
        Point hp=Point(bp.x,bp.y+ba,bp.z);
        Ellipsoid* head=(new Ellipsoid(Position(hp.x,hp.y,hp.z),ha,hb,hc));
        add(head);
        PhysicsManager::getInstance().add(new DistanceConstraint(body,head,bp+Point(0,ba,0),hp+Point(0,0,0)));

        //right arm
        float a=ba/2.0;
        float b=bb/2.0;
        float c=bc/2.0;
        Point p1=Point(bp.x+2*bb,bp.y+(0.5*ba),bp.z);
        Point p2=Point(p1.x+ 2*a,p1.y,p1.z);
        Ellipsoid* armRU=(new Ellipsoid(Position(p1.x,p1.y,p1.z),a,b,c));
        Ellipsoid* armRD=(new Ellipsoid(Position(p2.x,p2.y,p2.z),a,b,c));
        add(armRU->add(new MotionBehavior()));
        add(armRD->add(new MotionBehavior()));
        PhysicsManager::getInstance().add(new DistanceConstraint(body,armRU,bp+Point(bb,(0.5*ba),0),p1+Point(-bb,0,0)));
        PhysicsManager::getInstance().add(new DistanceConstraint(armRU,armRD,p1+Point(a,0,0),p2+Point(-a,0,0)));
        //left arm
        p1=Point(bp.x-2*bb,bp.y+(0.5*ba),bp.z);
        p2=Point(p1.x- 2*a,p1.y,p1.z);
        Ellipsoid* armLU=(new Ellipsoid(Position(p1.x,p1.y,p1.z),a,b,c));
        Ellipsoid* armLD=(new Ellipsoid(Position(p2.x,p2.y,p2.z),a,b,c));
        add(armLU->add(new MotionBehavior()));
        add(armLD->add(new MotionBehavior()));
        PhysicsManager::getInstance().add(new DistanceConstraint(body,armLU,bp+Point(-bb,(0.5*ba),0),p1+Point(bb,0,0)));
        PhysicsManager::getInstance().add(new DistanceConstraint(armLU,armLD,p1+Point(-a,0,0),p2+Point(a,0,0)));

        //right leg
        p1=Point(bp.x+2*bb,bp.y-(0.8*ba),bp.z);
        p2=Point(p1.x+ 2*a,p1.y,p1.z);
        Ellipsoid* legRU=(new Ellipsoid(Position(p1.x,p1.y,p1.z),a,b,c));
        Ellipsoid* legRD=(new Ellipsoid(Position(p2.x,p2.y,p2.z),a,b,c));
        add(legRU->add(new MotionBehavior()));
        add(legRD->add(new MotionBehavior()));
        PhysicsManager::getInstance().add(new DistanceConstraint(body,legRU,bp+Point(bb,-(0.8*ba),0),p1+Point(-bb,0,0)));
        PhysicsManager::getInstance().add(new DistanceConstraint(legRU,legRD,p1+Point(a,0,0),p2+Point(-a,0,0)));

        //left leg
        p1=Point(bp.x-2*bb,bp.y-(0.8*ba),bp.z);
        p2=Point(p1.x- 2*a,p1.y,p1.z);
        Ellipsoid* legLU=(new Ellipsoid(Position(p1.x,p1.y,p1.z),a,b,c));
        Ellipsoid* legLD=(new Ellipsoid(Position(p2.x,p2.y,p2.z),a,b,c));
        add(legLU->add(new MotionBehavior()));
        add(legLD->add(new MotionBehavior()));
        PhysicsManager::getInstance().add(new DistanceConstraint(body,legLU,bp+Point(-bb,-(0.8*ba),0),p1+Point(bb,0,0)));
        PhysicsManager::getInstance().add(new DistanceConstraint(legLU,legLD,p1+Point(-a,0,0),p2+Point(a,0,0)));

    }
    void test14(){
        add(new Ground(Position(0.0f, GROUND_LEVEL, 0.0f),300,300));
        Skeleton* mySkeleton=new Skeleton(Position(0,GROUND_LEVEL+2,5,0,180,0),"animation/skeleton.ani");
        //mySkeleton->setAcceleration(0,0,3);
        mySkeleton->add(new MotionBehavior());//->setRotates(false);
        add( mySkeleton );
        //
        add(new Animation(Position(0,1.8f+GROUND_LEVEL,0),"3DModel/human.obj","img/human.bmp"));
        //add(new Skeleton(Position(0,2,5),"animation/arms.ani"));

    }
    void testConstraint(){
        add(new Ground(Position(0.0f, GROUND_LEVEL, 0.0f),300,300));
        Component* sphere1=(new Sphere(Position(-5,30,10),0.5f));
        Component* box=(new Box(Position(5,20,10),2,2,2,"img/box.bmp"))->add(new MotionBehavior());
        add(sphere1);
        add(box);
        PhysicsManager::getInstance().add(new DistanceConstraint(sphere1,box,Point(-5,30,10),Point(5.0,20,10)));
        //PhysicsManager::getInstance().add(new DistanceConstraint(sphere1,box,Point(-5,30,10),Point(4.0,21,10)));
        //PhysicsManager::getInstance().add(new DistanceConstraint(sphere1,box));
    }
    void testStress(){
        add(new Ground(Position(0.0f,GROUND_LEVEL,0.0f),300,300));

        int w=60;
        int h=80;
        int d=60;

        add(new Plane(Position(-w/2.0f,h/2.0f,0.0f,0.0f,0.0f,90.0f),h,d,"img/box.bmp"));
        add(new Plane(Position(w/2.0f,h/2.0f,0.0f,0.0f,180.0f,90.0f),h,d,"img/box.bmp"));
        add(new Plane(Position(0.0f,h/2.0f,-d/2.0f,90.0f,0.0f,180.0f),w,h,"img/box.bmp"));
        add(new Plane(Position(0.0f,h/2.0f,d/2.0f,90.0f,0.0f,0.0f),w,h,"img/box.bmp"));

        for(int i=-10;i<10;i++){
            add((new Cylinder(Position(2.55f*i*0.5,10.0f,-2.55f*i),1.0,2.0,"img/red.bmp"))->add(new MotionBehavior()));
        }

        for(int i=-10;i<10;i++){
            add((new Sphere(Position(2.5f*i*0.6,20.0f,-2.5f*i),0.5f))->add(new MotionBehavior()));
        }

        for(int i=-10;i<10;i++){
            add((new Torus(Position(2.55f*i *0.7,30.0f,-2.55f*i),1.0f,0.5f))->add(new MotionBehavior()));
        }

        for(int i=-10;i<10;i++){
            add((new Ellipsoid(Position(2.55f*i *0.7,40.0f,-2.55f*i),0.5f,1.0,0.5))->add(new MotionBehavior()));
        }

        for(int i=-10;i<10;i++){
            add((new Model(Position(2.55f*i *0.7,50.0f,-2.55f*i),"3DModel/monkey.obj","img/default.bmp"))->add(new MotionBehavior()));
        }

        for(int i=-10;i<10;i++){
            add((new Box(Position(2.55f*i *0.7,60.0f,-2.55f*i),2,2,2,"img/box.bmp"))->add(new MotionBehavior()));
        }
    }

};
#endif

