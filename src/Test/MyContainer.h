#ifndef MyContainerH
#define MyContainerH

#include "../Component/Container.h"
#include "../Component/Sphere.h"
#include "../Component/Torus.h"
#include "../Component/Plane.h"
#include "../Component/Mountain.h"
#include "../Component/Tree.h"
#include "../Component/Water.h"
#include "../Component/Model.h"
#include "../Component/Animation.h"
#include "../Component/Box.h"
#include "../Component/Hut.h"
#include "../Component/Mill.h"
#include "../Component/Ground.h"
#include "../Component/Camera.h"
#include "../Component/InteractiveCamera.h"
#include "../Component/Light.h"
#include "../Component/Physics.h"

#include "../Behavior/MotionBehavior.h"



class MyContainer:public Container{
  public:
    MyContainer(Position&& position):Container(position){
			Box* my3DBox=new Box(Position(3.0f,0.0f,-25.0f));
			Box* my3DBox2=new Box(Position(-3.0f,0.0f,-25.0f));
			Hut* myHut=new Hut(Position(25.0f,0.0f,25.0f));
			Mill* myMill=new Mill(Position(35.0f,0.0f,-35.0f));
			Torus* myTorus=new Torus(Position(-10.0f,1.0f,-17.0f,90.0f,0.0f,0.0f),2.0f,1.0f);
			Ground* myGround=new Ground(Position(0.0f,0.0f,0.0f),100,100);
			Mountain* myMountain=new Mountain(Position(10.0f,19.0f,-49.0f));
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
			Model* myModel=new Model(Position(-15.0f,0.0f,-19.0f),"3DModel/monkey.obj");
			Animation* myAnimation=new Animation(Position(0.0f,0.4f,-0.0f),"3DModel/human.obj");
			InteractiveCamera* myInteractiveCamera=new InteractiveCamera(Position(0.0f,-3.0f,0.0f));
			Light* myLight=new Light(Position(40.0f,40.0f,40.0f));
			Sphere* mySphere=new Sphere(Position(0.0f,4.0f,-10.0f),0.39f);
			Sphere* mySphere2=new Sphere(Position(-3.0f,8.0f,-20.0f),0.5f);
			Sphere* mySphere3=new Sphere(Position(3.0f,6.0f,-20.0f),2.0f);
			Sphere* mySphere4=new Sphere(Position(-18.0f,40.0f,-30.0f),0.5f);
			
			Physics* physics=new Physics();
			
			
			add(my3DBox);
			add(my3DBox2->add(new MotionBehavior()));			
			add(myHut);
			add(myMill);
			add(myTorus);
			add(myGround);			
			add(myMountain);
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


			add(new Plane(Position(-15.0f,8.0f,-20.0f,0.0f,0.0f,90.0f),5.0f,5.0f,"img/box.bmp",2,2));
			add(new Plane(Position(15.0f,8.0f,-20.0f,0.0f,0.0f,90.0f),5.0f,5.0f,"img/box.bmp",2,2));
			add(new Plane(Position(-18.0f,20.0f,-17.0f,45.0f,0.0f,0.0f),5.0f,50.0f,"img/box.bmp",2,2));

			add(physics);
    }

};
#endif

