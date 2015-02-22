#ifndef EmitterH
#define EmitterH

#include "Container.h"
#include "Plane.h"
#include "../Effect/BlendingEffect.h"

class Emitter: public Container {  	
  public:

	  Emitter(Position position):Container(position){
	  	//for performance we disable these two
	  	setReflects(false);
	  	setCollides(false);
	  	add(new BlendingEffect());
	  	for(int i=0;i<512;i++){
	  		float x=i*0.1/512.0;
	  		Plane* particle=new Plane(Position(x,x,x,90.0,0,0),0.05,0.05,"img/particle.bmp",1,1);
	  		particle->add(new MotionBehavior())->add(new BlendingEffect())->setCollides(false);	  		
	  		add(particle);
	  	}
	  }

	virtual ~Emitter(){}

	//TODO:this is not the place...
	void onBeforeRenderFrame(){
		Container::onBeforeRenderFrame();

		vector<Component*>::iterator it;
		for(it=childs.begin();it!=childs.end();it++)
		{
			float x=(*it)->getPosition().getX()-position.getX();
			float y=(*it)->getPosition().getY()-position.getY();
			float z=(*it)->getPosition().getZ()-position.getZ();
			float n=sqrt(x*x+y*y +z*z);
			if(fabs(n)<0.001) n=1.0;
			//(*it)->setVelocity((rand()%100)/100.0-0.5,(rand()%100)/100.0-0.5,0);
			//(*it)->setVelocity(sin(y),sin(x),sin(z));
			(*it)->setVelocity(-y/n+(rand()%100)/100.0 -0.5,x/n+(rand()%100)/100.0-0.5,0.0);

			//(*it)->setVelocity(-z/(n*n),0.0,x/(n*n));
		}
	}

};


#endif
