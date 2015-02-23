#ifndef EmitterH
#define EmitterH

#include "Container.h"
#include "Surface.h"
#include "../Map/ConeMap.h"
#include "../Effect/BlendingEffect.h"
//TODO:when we generate the plane we are putting repeated points, so we are seeing just 2/3 of the points drawn.
//Find a way of either removing duplicated points or detach them to show all
class Emitter: public Container {  	
  public:

	  Emitter(Position position):Container(position){
		add(new BlendingEffect());
		Surface* particles1=new Surface(Position(0,0,0,0.0,0,0),ConeMap(0.2,0.2,24,24),"img/particle.bmp",GL_POINTS,"src/RenderStrategy/Shader/Particle.vs","src/RenderStrategy/Shader/Particle.fs");
		Surface* particles2=new Surface(Position(0,0,0,0.0,0,0),ConeMap(0.1,0.2,24,24),"img/particle.bmp",GL_POINTS,"src/RenderStrategy/Shader/Particle.vs","src/RenderStrategy/Shader/Particle.fs");
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
