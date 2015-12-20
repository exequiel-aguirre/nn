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
#include "../Component/Light.h"
#include "../Component/Physics.h"
#include "../Physics/Constraint/DistanceConstraint.h"
#include "../Component/Stats.h"
#include "../Behavior/MotionBehavior.h"



class CollisionContainer:public Container{
  private:
	const float GROUND_LEVEL=0.5;
  public:
    CollisionContainer(Position&& position):Container(position){
            testConstraint();

			add(new Camera(Position(0.0f,5.0f,100.0f)));
			add(new Light(Position(40.0f,40.0f,40.0f)));
			add(new Physics());
			add(new Stats());
			add(new Fog());
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
        add( (new Cylinder(Position(0,5,-70,90,0,0),2.0,100.0,"img/default.bmp"))/*->add(new MotionBehavior())*/ );
        add( (new Plane(Position(15,30,0),50,5,"img/box.bmp"))->add(new MotionBehavior()) );
    }
    void test7(){
        add(new Ground(Position(0.0f, GROUND_LEVEL, 0.0f, 2.0, 0.0, 2.0),300,300));
        add( (new Box(Position(5,10,-5),1,1,1,"img/box.bmp"))->add(new MotionBehavior()) );
        //add((new Sphere(Position(-5,15,10),1.5f))->add(new MotionBehavior()));
    }

    void testConstraint(){
        add(new Ground(Position(0.0f, GROUND_LEVEL, 0.0f),300,300));
        Component* sphere1=(new Sphere(Position(-5,30,10),0.5f));
        Component* box=(new Box(Position(5,20,10),2,2,2,"img/box.bmp"))->add(new MotionBehavior());
        add(sphere1);
        add(box);
        PhysicsManager::getInstance().add(new DistanceConstraint(sphere1,box,Point(-5,30,10),Point(4.0,20,10)));
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

