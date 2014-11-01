#ifndef MyContainerH
#define MyContainerH

#include "../Component/Container.h"
#include "../Component/Box.h"


class MyContainer:public Container{
  public:
    MyContainer(Position* position):Container(position){
			Box* my3DBox=new Box(new Position(-1.0f,0.0f,-19.0f),"/home/exe/Desktop/nn/Debug/NeHe.bmp");
			Box* my3DBox2=new Box(new Position(2.0f,0.0f,-19.0f),"/home/exe/Desktop/nn/Debug/NeHe.bmp");			
			
			add(my3DBox);
			add(my3DBox2);    
			
			
    
    }

};
#endif
