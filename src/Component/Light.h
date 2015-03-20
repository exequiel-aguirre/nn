#ifndef LightH
#define LightH

#include "Component.h"
#include "../DataStructure/RawLight.h"


class Light: public Component { 	
  private:
	bool isLightEnabled=false;
	float ambientMaterial[4]={ 0.2, 0.2, 0.2, 1.0};
	float diffuseMaterial[4]={ 0.8, 0.8, 0.8, 1.0};
	float specularMaterial[4]={1.0,1.0,1.0,1.0};
	float emissionMaterial[4]={0.0,0.0,0.0,0.0};//has no effect
	float ambientLight[4]= { 0.5f, 0.5f, 0.5f, 1.0f };
	float diffuseLight[4]= { 0.75f, 0.75f, 0.75f, 1.0f };
	float specularLight[4]={ 1.0f, 1.0f, 1.0f, 1.0f};
	float ambientLightModel[4]={ 0.2, 0.2, 0.2, 1.0};
  
  public:
	  Light(Position&& position):Component(position){
		RawLight rawLight;

		rawLight.shininess=128.0f;
		this->storeProduct(ambientMaterial,ambientLight,rawLight.ambientProduct);
		this->storeProduct(diffuseMaterial,diffuseLight,rawLight.diffuseProduct);
		this->storeProduct(specularMaterial,specularLight,rawLight.specularProduct);
		this->storeSceneColor(emissionMaterial,ambientMaterial,ambientLightModel,rawLight.sceneColor);

		float lightPosition[4] = {position.getX(),position.getY(),position.getZ(),1.0f};
		std::copy(lightPosition, lightPosition+4, rawLight.position);
		glEnable(GL_LIGHT0);


		RenderStrategy::getInstance().setRawLight(rawLight);
		//turn off the light
		toggleLight();
		
	  }		

    virtual ~Light(){}


    void storeSceneColor(float emissionMaterial[4],float ambientMaterial[4],float ambientLightModel[4],float sceneColor[4]){
		for(int i=0;i<4;i++){
			sceneColor[i]=emissionMaterial[i] + ambientMaterial[i]*ambientLightModel[i];//Ecm + Acm*Acs
		}
    }

    void storeProduct(float material[4],float light[4],float product[4]){
		for(int i=0;i<4;i++){
			product[i]=light[i]*material[i];
		}
    }
    void toggleLight()
	{
		if(!isLightEnabled)
		{
			glEnable(GL_LIGHTING);
		}
		else
		{
			glDisable(GL_LIGHTING);
		}
	}

};


#endif
