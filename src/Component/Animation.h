#ifndef AnimationH
#define AnimationH

#include "Model.h"
#include <GL/gl.h>
#include "../Utils/Utils.h"
#include "../Utils/ModelObject.h"
#include <vector>
#include <sstream>
using std::vector;


class Animation: public Model {  
  protected:	
	vector<ModelObject*>* modelObjects;
	vector<ModelObject*>::iterator currentModelObject;
	unsigned int frames=0;

  public:
	  Animation(Position* position,char* modelFilename):Model(position,modelFilename){		
		modelObjects=new vector<ModelObject*>();		
	  	modelObjects->push_back(this->modelObject);
	  	this->loadAnimation(modelFilename);	  	
    	currentModelObject=modelObjects->begin();    	
	 }		

    virtual ~Animation(){}
    
    void render(){
		frames++;
		if(frames>2){
			frames=frames%2;
			currentModelObject++;    			
			if(currentModelObject==modelObjects->end()){
				currentModelObject=modelObjects->begin();
			}
    	}
    	//we set the current model object and ask the model to render normally
		this->modelObject=(*currentModelObject);
		Model::render();
    }


    int loadAnimation(char* modelFilename){
    	//load the animation.
	  	std:string str(modelFilename);
	  	str.replace(str.find(".obj"), 4, "");
	  	for(int i=0;i<30;i++)
	  	{	  		
	  		std::stringstream tmp;
	  		tmp<<str<<"_"<<i<<".obj";
	  		std::ifstream f(tmp.str().c_str());
		    if (f.good()) {
		        f.close();
		        modelObjects->push_back(Utils::loadModel(tmp.str().c_str()));
			}
			else
			{
				f.close();
				break;
			}
		}
		return modelObjects->size();
    }
    

};


#endif
