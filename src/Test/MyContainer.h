#ifndef MyContainerH
#define MyContainerH

#include "../Component/Container.h"
#include "../Component/Box.h"
#include "../Component/Ground.h"
#include "../Component/Camera.h"


class MyContainer:public Container{
  public:
    MyContainer(Position* position):Container(position){
			Box* my3DBox=new Box(new Position(0.0f,0.0f,-19.0f),NULL);
			Ground* myGround=new Ground(new Position(0.0f,-1.0f,0.0f));
			Camera* myCamera=new Camera(new Position(0.0f,-1.0f,0.0f));
			//Box* my3DBox2=new Box(new Position(-1.0f,0.0f,-2.0f),NULL);
			
			add(my3DBox);
			add(myGround);
			add(myCamera);
			//add(my3DBox2);
    
    }

};
#endif
