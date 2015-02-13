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
      Component::render();
      vector<Component*>::iterator it;
      for(it=childs.begin();it!=childs.end();it++)
    	{
        	(*it)->render();
      }
	}


	Container* add(Component* child)
	{
      child->getPosition()+=(this->position);
      //TODO:find a way to avoid this
      child->calculateBoundary();
      childs.push_back(child);
      if(child->getModelObject().getSize()!=0){//if the object has no boundary the collision detector won't work, and no physics can be applied
        PhysicsManager::getInstance()->add(child);
      }
      return this;
	}

  vector<Component*> getChilds(){
    return this->childs;
  }
		
};
#endif
