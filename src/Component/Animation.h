#ifndef AnimationH
#define AnimationH

#include "Model.h"


class Animation: public Model {
  protected:
	vector<ModelObject> modelObjects;
	vector<ModelObject>::iterator currentModelObject;
	unsigned int frames=0;

  public:  	 
	Animation(Position&& position,const char* modelFilename):Model(position,modelFilename){
		modelObjects.push_back(this->modelObject);
		this->loadAnimation(modelFilename);
		currentModelObject=modelObjects.begin();
	}

    virtual ~Animation(){}


    void render(){
		frames++;
		if(frames>4){
			frames=frames%4;
			currentModelObject++;
			if(currentModelObject==modelObjects.end()){
				currentModelObject=modelObjects.begin();
			}
		}

		RenderStrategy::getInstance().render(this->positionMatrix,(*currentModelObject),shader,texture);
    }


    int loadAnimation(const char* modelFilename){
		//load the animation.
		for(int i=0;i<30;i++)
		{
			std::string frameFilename=Utils::getAnimationFrameFilename(modelFilename,i);
			std::ifstream f(frameFilename.c_str());
		    if (f.good()) {
				f.close();
				ModelObject modelObject=Utils::loadModel(frameFilename.c_str());
				RenderStrategy::getInstance().initModelObject(modelObject,GL_TRIANGLES);

				modelObjects.push_back(modelObject);
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
