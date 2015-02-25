#ifndef EmitterH
#define EmitterH

#include "Container.h"
#include "Surface.h"
#include "../Map/ConeMap.h"
#include "../Map/RandomizedDecorator.h"
#include "../Effect/BlendingEffect.h"

class Emitter: public Container {  	
  public:

	  Emitter(Position position):Container(position){
		add(new BlendingEffect());
		Surface* particles1=new Surface(Position(0,0.5,0,0.0,0,0),RandomizedDecorator(new ConeMap(0.4,0.6,24,24)),"img/particle.bmp",GL_POINTS,"src/RenderStrategy/Shader/Particle.vs","src/RenderStrategy/Shader/Particle.fs");
		Surface* particles2=new Surface(Position(0,0.5,0,0.0,0,0),RandomizedDecorator(new ConeMap(0.2,0.6,24,24)),"img/particle.bmp",GL_POINTS,"src/RenderStrategy/Shader/Particle.vs","src/RenderStrategy/Shader/Particle.fs");
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
