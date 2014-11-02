#ifndef MyContainerH
#define MyContainerH

#include "../Component/Container.h"
#include "../Component/Sphere.h"
#include "../Component/Box.h"
#include "../Component/Ground.h"
#include "../Component/Camera.h"
#include "TimeBehavior.h"


class MyContainer:public Container{
  public:
    MyContainer(Position* position):Container(position){
			Box* my3DBox=new Box(new Position(0.0f,0.0f,-19.0f),NULL);
			Box* my3DBox2=new Box(new Position(-3.0f,0.0f,-19.0f),NULL);
			Sphere* mySphere=new Sphere(new Position(0.0f,0.0f,-7.0f),NULL);
			Ground* myGround=new Ground(new Position(0.0f,-1.0f,0.0f));
			Camera* myCamera=new Camera(new Position(0.0f,-1.0f,0.0f));			
			
			add(my3DBox);
			add(my3DBox2->add(new TimeBehavior()));
			add(mySphere);
			add(myGround);
			add(myCamera);
			//add(my3DBox2);
    
    }

};
#endif
