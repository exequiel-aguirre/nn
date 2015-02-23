#ifndef EmitterH
#define EmitterH

#include "Container.h"
#include "Plane.h"
#include "../Effect/BlendingEffect.h"

class Emitter: public Container {  	
  public:

	  Emitter(Position position):Container(position){
		add(new BlendingEffect());
		Plane* particles1=new Plane(Position(0,0,0,90.0,0,0),0.2,0.2,"img/particle.bmp",40,40,GL_POINTS,"src/RenderStrategy/Shader/Particle.vs","src/RenderStrategy/Shader/Particle.fs");
		Plane* particles2=new Plane(Position(0,0,0,00.0,0,90.0),0.2,0.2,"img/particle.bmp",40,40,GL_POINTS,"src/RenderStrategy/Shader/Particle.vs","src/RenderStrategy/Shader/Particle.fs");  		
		particles1->add(new MotionBehavior())->add(new BlendingEffect())->setCollides(false);
		particles2->add(new MotionBehavior())->add(new BlendingEffect())->setCollides(false);
		add(particles1)->add(particles2);
	  }

	virtual ~Emitter(){}

	void render(){
		glEnable(GL_PROGRAM_POINT_SIZE);
			Container::render();
		glDisable(GL_PROGRAM_POINT_SIZE);
	}
};


#endif
