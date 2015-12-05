#ifndef ContainerH
#define ContainerH
#include "Component.h"
#include "../Physics/PhysicsManager.h"
#include <vector>

class Container: public Component {
  protected:
    vector<Component*> childs;
  
  public:
  using Component::add;
  Container(Position& position):Component(position){}

  Container(Position&& position):Container(position){};

	virtual ~Container(){}  
  

  void onBeforeRenderFrame(){
      vector<Component*>::iterator it;
      for(it=childs.begin();it!=childs.end();it++)
      {
         (*it)->onBeforeRenderFrame(); 
      }
  } 

	void render()
	{
      Component::doEffects();
      RenderStrategy::getInstance().render(this->modelMatrix,this->modelObject,this->shader,this->texture);
      vector<Component*>::iterator it;
      for(it=childs.begin();it!=childs.end();it++)
    	{
        	(*it)->render();
      }
      Component::undoEffects();
	}

  void setPosition(float x,float y,float z,float phi,float theta,float psi){
    Position deltaPosition=Position(x,y,z,phi,theta,psi)-position;
    Component::setPosition(x,y,z,phi,theta,psi);
    vector<Component*>::iterator it;
      for(it=childs.begin();it!=childs.end();it++)
      {
          Position p=(*it)->getPosition()+deltaPosition;
          (*it)->setPosition(p.getX(),p.getY(),p.getZ(),p.getPhi(),p.getTheta(),p.getPsi());
      }
  }

	Container* add(Component* child)
	{
      Position p=child->getPosition()+this->position;
      child->setPosition(p.getX(),p.getY(),p.getZ(),p.getPhi(),p.getTheta(),p.getPsi());

      childs.push_back(child);
      if(child->getModelObject().getSize()!=0 && child->getCollides()){//if the object has no boundary the collision detector won't work, and no physics can be applied
        PhysicsManager::getInstance().add(child);
      }
      return this;
	}

  /*This should behave just like add, but with a better performance
  * The disadvantage, is that all merged components must have the same texture and shader
  */
  Container* merge(Component* child){
    this->modelObject.merge(child->getModelObject(),child->getModelMatrix());
    this->shader=child->getShader();
    this->texture=child->getTexture();
    delete(child);//Once merged, this is not needed anymore

    return this;
  }

  vector<Component*> getChilds(){
    return this->childs;
  }
		
};
#endif
