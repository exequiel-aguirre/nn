#ifndef ContainerH
#define ContainerH
#include "Component.h"
#include "../Physics/PhysicsManager.h"
#include <vector>

class Container: public Component {
  private:
    vector<Component*>* childs;
  
  public:
  using Component::add;
	Container(Position* position):Component(position)
	{
    	this->childs=new vector<Component*>();
	}
	virtual ~Container(){}  
  

  void onBeforeRenderFrame(){
      vector<Component*>::iterator it;
      for(it=childs->begin();it!=childs->end();it++)
      {
         (*it)->onBeforeRenderFrame(); 
      }
  }
  void onBeforeRender(){
    //do not translate anything
    doEffects();
  } 
  
	void render()
	{
    	vector<Component*>::iterator it;
      
    	for(it=childs->begin();it!=childs->end();it++)
    	{
          (*it)->onBeforeRender();
        	(*it)->render();
          (*it)->onAfterRender();

      	}
	}
  void onAfterRender(){
    //do not translate anything
    undoEffects();
  }
		
	Container* add(Component* child)
	{
    	*(child->getPosition())+=(this->position);
      //TODO:find a way to avoid this
      child->calculateBoundary();
    	childs->push_back(child);
      PhysicsManager::getInstance()->add(child);
    	return this;
	}
		
		
};
#endif
