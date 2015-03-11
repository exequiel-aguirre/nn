#ifndef LightH
#define LightH

#include "Component.h"
#include "../DataStructure/RawLight.h"
#include <GL/gl.h>


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
		float ambientProduct[4]={0};
		float diffuseProduct[4]={0};
		float specularProduct[4]={0};
		float sceneColor[4]={0};


		rawLight.shininess=128.0f;

		this->getProduct(ambientMaterial,ambientLight,ambientProduct);
		std::copy(ambientProduct, ambientProduct+4, rawLight.ambientProduct);

		this->getProduct(diffuseMaterial,diffuseLight,diffuseProduct);
		std::copy(diffuseProduct, diffuseProduct+4, rawLight.diffuseProduct);

		this->getProduct(specularMaterial,specularLight,specularProduct);
		std::copy(specularProduct, specularProduct+4, rawLight.specularProduct);

		this->getSceneColor(emissionMaterial,ambientMaterial,ambientLightModel,sceneColor);
		std::copy(sceneColor, sceneColor+4, rawLight.sceneColor);

		auto lightPosition = std::initializer_list<double>({position.getX(),position.getY(),position.getZ(),1.0f});
		std::copy(lightPosition.begin(), lightPosition.end(), rawLight.position);
		glEnable(GL_LIGHT0);


		RenderStrategy::getInstance().setRawLight(rawLight);
		//turn off the light
		toggleLight();
		
	  }		

    virtual ~Light(){}

	//TODO:find a better way of doing this
    void getSceneColor(float emissionMaterial[4],float ambientMaterial[4],float ambientLightModel[4],float sceneColor[4]){
		this->getProduct(ambientMaterial,ambientLightModel,sceneColor);
		for(int i=0;i<4;i++) sceneColor[i]+=emissionMaterial[i];//Ecm + Acm*Acs
    }
    //TODO:find a better way of doing this
    void getProduct(float material[4],float light[4],float product[4]){
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
