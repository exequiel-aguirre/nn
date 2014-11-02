#ifndef ContainerH
#define ContainerH
#include "Component.h"
#include <vector>

class Container: public Component {
  private:
    vector<Component*>* childs;
  
  public:
	Container(Position* position):Component(position)
	{
    	this->childs=new vector<Component*>();
	}
	virtual ~Container(){}
	

	void onBeforeRender()
	{
    	vector<Component*>::iterator it;
      
    	for(it=childs->begin();it!=childs->end();it++)
    	{
        	(*it)->onBeforeRender();
      	}
	}

	void render()
	{
    	vector<Component*>::iterator it;
      
    	for(it=childs->begin();it!=childs->end();it++)
    	{
        	(*it)->render();
      	}
	}

	void onAfterRender()
	{
    	vector<Component*>::iterator it;
      
    	for(it=childs->begin();it!=childs->end();it++)
    	{
        	(*it)->onAfterRender();
      	}
	}
		
	Container* add(Component* child)
	{
    	child->getPosition()->setParent(this->position);
    	childs->push_back(child);
    	return this;
	}
		
		
};
#endif
