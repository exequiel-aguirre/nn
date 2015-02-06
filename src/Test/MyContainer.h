#ifndef MyContainerH
#define MyContainerH

#include "../Component/Container.h"
#include "../Component/Sphere.h"
#include "../Component/Ellipsoid.h"
#include "../Component/Torus.h"
#include "../Component/Plane.h"
#include "../Component/Mountain.h"
#include "../Component/Cloud.h"
#include "../Component/Tree.h"
#include "../Component/Water.h"
#include "../Component/Model.h"
#include "../Component/Animation.h"
#include "../Component/Box.h"
#include "../Component/SkyBox.h"
#include "../Component/Hut.h"
#include "../Component/Mill.h"
#include "../Component/Ground.h"
#include "../Component/Terrain.h"
#include "../Component/Camera.h"
#include "../Component/InteractiveCamera.h"
#include "../Component/Background.h"
#include "../Effect/Fog.h"
#include "../Component/Light.h"
#include "../Component/Physics.h"

#include "../Behavior/MotionBehavior.h"



class MyContainer:public Container{
  public:
    MyContainer(Position&& position):Container(position){
			Box* my3DBox=new Box(Position(3.0f,0.0f,-25.0f));
			Box* my3DBox2=new Box(Position(-3.0f,0.0f,-25.0f));
			//SkyBox* mySkyBox=new SkyBox(Position(0.0f,-1.0f,0.0f),400,400,400,"img/skybox_bottom.bmp","img/skybox_top.bmp","img/skybox_left.bmp","img/skybox_right.bmp","img/skybox_back.bmp","img/skybox_front.bmp");
			Hut* myHut=new Hut(Position(25.0f,0.0f,25.0f));
			Mill* myMill=new Mill(Position(35.0f,0.0f,-35.0f));
			Torus* myTorus=new Torus(Position(-10.0f,1.0f,-17.0f,90.0f,0.0f,0.0f),2.0f,1.0f);
			Ground* myGround=new Ground(Position(0.0f,0.0f,0.0f),100,100);
			Terrain* myTerrain=new Terrain(Position(0.0f,1.0f,-5.0f),2,2,"img/terrain.bmp");
			Mountain* myMountain=new Mountain(Position(10.0f,19.0f,-49.0f));
			Cloud* myCloud1=new Cloud(Position(-100.0f,90.0f,-70.0f),15.0f,2.0f,10.0f);
			Cloud* myCloud2=new Cloud(Position(100.0f,90.0f,70.0f),15.0f,2.0f,20.0f);
			Cloud* myCloud3=new Cloud(Position(100.0f,90.0f,-40.0f),5.0f,2.0f,15.0f);
			Cloud* myCloud4=new Cloud(Position(-10.0f,85.0f,-120.0f),5.0f,2.0f,10.0f);
			Cloud* myCloud5=new Cloud(Position(-20.0f,85.0f,100.0f),15.0f,2.0f,10.0f);
			Cloud* myCloud6=new Cloud(Position(50.0f,100.0f,-100.0f),15.0f,2.0f,5.0f);
			Tree* myTree1=new Tree(Position(5.0f,0.0f,5.0f));
			Tree* myTree2=new Tree(Position(5.0f,0.0f,10.0f));
			Tree* myTree3=new Tree(Position(5.0f,0.0f,15.0f));
			Tree* myTree4=new Tree(Position(-5.0f,0.0f,5.0f));
			Tree* myTree5=new Tree(Position(-5.0f,0.0f,10.0f));
			Tree* myTree6=new Tree(Position(-5.0f,0.0f,15.0f));
			Water* myWaterF=new Water(Position(0.0f,0.0f,-100.0f),100,100);
			Water* myWaterR=new Water(Position(100.0f,0.0f,0.0f),100,300);
			Water* myWaterB=new Water(Position(0.0f,0.0f,100.0f),100,100);
			Water* myWaterL=new Water(Position(-100.0f,0.0f,0.0f),100,300);
			Model* myModel=new Model(Position(-15.0f,4.0f,-19.0f),"3DModel/monkey.obj");
			Animation* myAnimation=new Animation(Position(2.0f,2.5f,-15.0f),"3DModel/human.obj");
			InteractiveCamera* myInteractiveCamera=new InteractiveCamera(Position(0.0f,3.0f,0.0f));
			//Background* myBackground=new Background({1.000, 0.941, 0.961,1});
			Fog* myFog=new Fog();
			Light* myLight=new Light(Position(40.0f,40.0f,40.0f));
			Sphere* mySphere=new Sphere(Position(0.0f,4.0f,-10.0f),0.39f);
			Sphere* mySphere2=new Sphere(Position(-3.0f,8.0f,-20.0f),0.5f);
			Sphere* mySphere3=new Sphere(Position(3.0f,6.0f,-20.0f),2.0f);
			Sphere* mySphere4=new Sphere(Position(-18.0f,40.0f,-30.0f),0.5f);
			Ellipsoid* myEllipsoid=new Ellipsoid(Position(-0.0f,6.0f,-20.0f),1.0f,2.0f,1.0f);
			
			Physics* physics=new Physics();
			
			//add(myBackground);
			add(myFog);
			add(my3DBox);
			add(my3DBox2->add(new MotionBehavior()));			
			//add(mySkyBox);
			add(myHut);
			add(myMill);
			add(myTorus->add(new MotionBehavior()));
			add(myGround);
			add(myTerrain);
			add(myMountain);
			add(myCloud1);add(myCloud2);add(myCloud3);add(myCloud4);add(myCloud5);add(myCloud6);
			add(myTree1);add(myTree2);add(myTree3);add(myTree4);add(myTree5);add(myTree6);
			add(myWaterF);add(myWaterR);add(myWaterB);add(myWaterL);
			add(myModel->add(new MotionBehavior()));
			myAnimation->getVelocity().setZ(8.0f);add(myAnimation->add(new MotionBehavior()));
			add(myInteractiveCamera);
			add(myLight);
			add(mySphere->add(new MotionBehavior()));
			mySphere2->getVelocity().setX(40.0f);add(mySphere2->add(new MotionBehavior()));
			add(mySphere3->add(new MotionBehavior()));
			add(mySphere4->add(new MotionBehavior()));
			add(myEllipsoid->add(new MotionBehavior()));


			add(new Plane(Position(-15.0f,8.0f,-20.0f,0.0f,0.0f,90.0f),5.0f,5.0f,"img/box.bmp",2,2));
			add(new Plane(Position(15.0f,8.0f,-20.0f,0.0f,0.0f,90.0f),5.0f,5.0f,"img/box.bmp",2,2));
			add(new Plane(Position(-18.0f,20.0f,-17.0f,45.0f,0.0f,0.0f),5.0f,50.0f,"img/box.bmp",2,2));

			add(physics);
    }

};
#endif

