#ifndef AnimationStrategyH
#define AnimationStrategyH

#include "TextureStrategy.h"
#include "../Utils/Utils.h"
#include "../DataStructure/ModelObject.h"
#include <vector>
#include <sstream>



class AnimationStrategy: public TextureStrategy {  
  protected:	
	vector<ModelObject> modelObjects;
	vector<ModelObject>::iterator currentModelObject;
	unsigned int frames=0;

  public:
	  AnimationStrategy(char* modelFilename,char* textureFilename):TextureStrategy(modelFilename,textureFilename){		
		modelObjects.push_back(this->modelObject);
		this->loadAnimation(modelFilename);
		currentModelObject=modelObjects.begin();
	 }		

    virtual ~AnimationStrategy(){}
    
    void render(){
		frames++;
		if(frames>2){
			frames=frames%2;
			currentModelObject++;    			
			if(currentModelObject==modelObjects.end()){
				currentModelObject=modelObjects.begin();
			}
    	}
    	//we set the current model object and ask the parent strategy to render normally
		this->modelObject=(*currentModelObject);
		TextureStrategy::render();
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
