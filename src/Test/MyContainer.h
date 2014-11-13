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
#include "../Component/Ground.h"
#include "../Component/Camera.h"
#include "../Component/Light.h"

#include "TimeBehavior.h"


class MyContainer:public Container{
  public:
    MyContainer(Position* position):Container(position){
			Box* my3DBox=new Box(new Position(0.0f,0.0f,-19.0f),NULL);
			Box* my3DBox2=new Box(new Position(-3.0f,0.0f,-19.0f),NULL);
			Sphere* mySphere=new Sphere(new Position(0.0f,0.0f,-7.0f));			
			Torus* myTorus=new Torus(new Position(-10.0f,2.0f,-17.0f));			
			Plane* myPlane=new Plane(new Position(0.0f,-1.0f,0.0f),100,100,"img/ground.bmp");
			Mountain* myMountain=new Mountain(new Position(10.0f,18.0f,-49.0f));
			Tree* myTree1=new Tree(new Position(5.0f,0.0f,-5.0f));
			Tree* myTree2=new Tree(new Position(5.0f,0.0f,-10.0f));
			Tree* myTree3=new Tree(new Position(5.0f,0.0f,-15.0f));
			Tree* myTree4=new Tree(new Position(-5.0f,0.0f,-5.0f));
			Tree* myTree5=new Tree(new Position(-5.0f,0.0f,-10.0f));
			Tree* myTree6=new Tree(new Position(-5.0f,0.0f,-15.0f));
			Water* myWaterF=new Water(new Position(0.0f,-1.0f,-100.0f),100,100);
			Water* myWaterR=new Water(new Position(100.0f,-1.0f,0.0f),100,300);
			Water* myWaterB=new Water(new Position(0.0f,-1.0f,100.0f),100,100);
			Water* myWaterL=new Water(new Position(-100.0f,-1.0f,0.0f),100,300);
			Model* myModel=new Model(new Position(-15.0f,-1.0f,-19.0f),"3DModel/monkey.obj");
			Animation* myAnimation=new Animation(new Position(-0.0f,-1.0f,-19.0f),"3DModel/human.obj");
			Ground* myGround=new Ground(new Position(0.0f,-1.0f,0.0f),NULL);
			Camera* myCamera=new Camera(new Position(0.0f,-1.0f,0.0f));			
			Light* myLight=new Light(new Position(40.0f,40.0f,40.0f));

			
			add(my3DBox);
			add(my3DBox2->add(new TimeBehavior()));			
			//add(mySphere);
			add(myTorus);
			add(myMountain);
			add(myTree1);add(myTree2);add(myTree3);add(myTree4);add(myTree5);add(myTree6);
			add(myWaterF);add(myWaterR);add(myWaterB);add(myWaterL);
			add(myModel);
			add(myAnimation->add(new TimeBehavior()));
			//add(myGround);
			add(myPlane);
			add(myCamera);
			add(myLight);
    
    }

};
#endif

