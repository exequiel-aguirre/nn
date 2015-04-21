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
		Surface* particles1=new Surface(Position(0,0.5,0,0.0,0,0),RandomizedDecorator(new ConeMap(0.4,0.6,24,24)),NULL,GL_POINTS,"Particle");
		Surface* particles2=new Surface(Position(0,0.5,0,0.0,0,0),RandomizedDecorator(new ConeMap(0.2,0.6,24,24)),NULL,GL_POINTS,"Particle");
		particles1->add(new BlendingEffect())->setCollides(false)->getShader().setTimeEnabled(true);
		particles2->add(new BlendingEffect())->setCollides(false)->getShader().setTimeEnabled(true);
		add(particles1)->add(particles2);
		glEnable(GL_PROGRAM_POINT_SIZE);
	  }

	virtual ~Emitter(){}

};


#endif
