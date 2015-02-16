#ifndef AnimationStrategyH
#define AnimationStrategyH

#include "RenderStrategy3.h"
#include "../Utils/Utils.h"
#include "../DataStructure/ModelObject.h"
#include <vector>
#include <sstream>



class AnimationStrategy: public RenderStrategy3 {
  protected:	
	vector<ModelObject> modelObjects;
	vector<ModelObject>::iterator currentModelObject;
	unsigned int frames=0;

  public:
	  AnimationStrategy(char* modelFilename,char* textureFilename):RenderStrategy3(modelFilename,textureFilename,GL_TRIANGLES){
		modelObjects.push_back(this->modelObject);
		this->loadAnimation(modelFilename);
		currentModelObject=modelObjects.begin();
	 }		

    virtual ~AnimationStrategy(){}
    
    void render(Position& position){
		frames++;
		if(frames>4){
			frames=frames%4;
			currentModelObject++;    			
			if(currentModelObject==modelObjects.end()){
				currentModelObject=modelObjects.begin();
			}
    	}
    	//we set the current model object and ask the parent strategy to render normally
		this->modelObject=(*currentModelObject);
		RenderStrategy3::render(position);
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
		        modelObjects.push_back(this->loadModel(tmp.str().c_str()));
			}
			else
			{
				f.close();
				break;
			}
		}
		return modelObjects.size();
    }
    

};


#endif
