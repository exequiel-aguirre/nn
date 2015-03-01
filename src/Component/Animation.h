#ifndef AnimationH
#define AnimationH

#include "Model.h"


class Animation: public Model {
  protected:
	vector<ModelObject> modelObjects;
	vector<ModelObject>::iterator currentModelObject;
	unsigned int frames=0;

  public:  	 
	Animation(Position&& position,char* modelFilename):Model(position,modelFilename){
		modelObjects.push_back(this->modelObject);
		this->loadAnimation(modelFilename,"img/human.bmp");//TODO:avoid hardcoding this
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

		this->renderStrategy.render(this->position,(*currentModelObject),shader);
    }


    int loadAnimation(char* modelFilename,char* textureFilename){
		//load the animation.
		for(int i=0;i<30;i++)
		{
			std::string frameFilename=Utils::getAnimationFrameFilename(modelFilename,i);
			std::ifstream f(frameFilename.c_str());
		    if (f.good()) {
				f.close();
				ModelObject modelObject=Utils::loadModel(frameFilename.c_str());
				this->renderStrategy.initModelObject(modelObject,textureFilename,GL_TRIANGLES);

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
