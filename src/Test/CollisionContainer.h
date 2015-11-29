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
#include "../Component/Stats.h"
#include "../Behavior/MotionBehavior.h"



class CollisionContainer:public Container{
  private:
	const float GROUND_LEVEL=0.5;
  public:
    CollisionContainer(Position&& position):Container(position){

			Ground* myGround=new Ground(Position(0.0f,GROUND_LEVEL,0.0f),300,300);
			
			Box* my3DBox=new Box(Position(-53.0f,GROUND_LEVEL,-25.0f));
			Box* my3DBox2=new Box(Position(-50.0f,GROUND_LEVEL+2.0,-25.0f));
			//Hut* myHut=new Hut(Position(25.0f,GROUND_LEVEL,25.0f));			
			//Torus* myTorus=new Torus(Position(-70.0f,1.0f+GROUND_LEVEL,-19.0f,90.0f,0.0f,0.0f),2.0f,1.0f);
			
			Sphere* mySphere=new Sphere(Position(-50.0f,4.0f,-10.0f),0.39f);
			Sphere* mySphere2=new Sphere(Position(-60.0f,8.0f,-20.0f),0.5f);
			Sphere* mySphere3=new Sphere(Position(-50.0f,6.0f,-20.0f),2.0f);
			Sphere* mySphere4=new Sphere(Position(-70.0f,40.0f,-30.0f),0.5f);
			Ellipsoid* myEllipsoid=new Ellipsoid(Position(-60.0f,6.0f,-30.0f),1.0f,2.0f,1.0f);

			
			Camera* myInteractiveCamera=new Camera(Position(0.0f,60.0f,0.0f));
			Light* myLight=new Light(Position(40.0f,40.0f,40.0f));
			Physics* physics=new Physics();


			add(myGround);


			add(my3DBox);
			add(my3DBox2->add(new MotionBehavior()));
			//add(myHut);			
			//add(myTorus->add(new MotionBehavior()));
			add(mySphere->add(new MotionBehavior()));
			mySphere2->getVelocity().setX(40.0f);add(mySphere2->add(new MotionBehavior()));
			add(mySphere3->add(new MotionBehavior()));
			add(mySphere4->add(new MotionBehavior()));
			add(myEllipsoid->add(new MotionBehavior()));
			add(new Plane(Position(-65.0f,8.0f,-20.0f,0.0f,0.0f,90.0f),10.0f,10.0f,"img/box.bmp"));
			add(new Plane(Position(-43.0f,8.0f,-20.0f,0.0f,0.0f,90.0f),15.0f,15.0f,"img/box.bmp"));
			add(new Plane(Position(-70.0f,20.0f,-17.0f,45.0f,0.0f,0.0f),5.0f,50.0f,"img/box.bmp"));


			//add(new Box(Position(0,GROUND_LEVEL+0.1,0),50,60,50,"img/box.bmp"));
			int w=50;
			int h=80;
			int d=50;
			//add(new Plane(Position(0.0f,0.0f,0.0f),w,d,bottom));
			//add(new Plane(Position(0.0f,h,0.0f),w,d,top));
			add(new Plane(Position(-w/2.0f,h/2.0f,0.0f,0.0f,0.0f,90.0f),h,d,"img/box.bmp"));
			add(new Plane(Position(w/2.0f,h/2.0f,0.0f,0.0f,180.0f,90.0f),h,d,"img/box.bmp"));
			add(new Plane(Position(0.0f,h/2.0f,-d/2.0f,90.0f,0.0f,180.0f),w,h,"img/box.bmp"));
			add(new Plane(Position(0.0f,h/2.0f,d/2.0f,90.0f,0.0f,0.0f),w,h,"img/box.bmp"));
			Cylinder* cylinder;
			for(int i=-10;i<=10;i++){
				cylinder=new Cylinder(Position(2.55f*i*0.5,10.0f,-2.55f*i),0.5,2.0,"img/red.bmp");
				add(cylinder->add(new MotionBehavior()));
			}
			Sphere* sphere;
			for(int i=-10;i<=10;i++){
				sphere=new Sphere(Position(2.5f*i*0.6,20.0f,-2.5f*i),0.5f);
				add(sphere->add(new MotionBehavior()));
			}
			Torus* torus;
			for(int i=-10;i<=10;i++){
				torus=new Torus(Position(2.55f*i *0.7,30.0f,-2.55f*i),1.0f,0.5f);
				add(torus->add(new MotionBehavior()));
			}
			Ellipsoid* ellipsoid;
			for(int i=-10;i<=10;i++){
				ellipsoid=new Ellipsoid(Position(2.55f*i *0.7,40.0f,-2.55f*i),0.5f,1.0,0.5);
				add(ellipsoid->add(new MotionBehavior()));
			}		
			Model* monkey;
			for(int i=-10;i<=10;i++){
				monkey=new Model(Position(2.55f*i *0.7,50.0f,-2.55f*i),"3DModel/monkey.obj","img/default.bmp");
				add(monkey->add(new MotionBehavior()));
			}		

			add(myInteractiveCamera);
			add(myLight);
			add(physics);
			add(new Stats());
			add(new Fog());


    }

};
#endif

