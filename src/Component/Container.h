#ifndef ContainerH
#define ContainerH
#include "Component.h"
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
		
	Container* add(Component* child)
	{
    	child->getPosition()->setParent(this->position);
    	childs->push_back(child);
    	return this;
	}
		
		
};
#endif
