#ifndef ShadowH
#define ShadowH
#include "IEffect.h"
#include "../Utils/Utils.h"

class Shadow:public IEffect{  
  private:
    Matrix projectionMatrix;
    Component* light;//TODO:use a light reference
  	GLuint depthMapId;//TODO:use ResourceManager
    GLuint frameBuffer;
    Shader basicShader;
    Texture basicTexture;
    //For the shadow we render from the light's point of view and based on that, we can decide where the shadows are, when we
    //do the normal Render. In this case we are using the same projection matrix, but that can be changed.
  public:
	Shadow(Component* light){        
        this->light=light;
        this->basicShader=ResourceManager::getInstance().getShader("Basic");
        this->basicTexture=ResourceManager::getInstance().getTexture("img/default.bmp");

        int cameraViewPort[4];
        glGetIntegerv(GL_VIEWPORT,cameraViewPort);
        unsigned int width=cameraViewPort[2];
        unsigned int height=cameraViewPort[3];
        depthMapId=Utils::createDepthMap(width,height);

        glGenFramebuffers(1,&frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER,frameBuffer);
        //this is to save the rendered frame to the depthMap
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,depthMapId,0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        //we bind it so it can be use by the normal render
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D,depthMapId);
        
	}
    ~Shadow(){
        glDeleteTextures(1,&depthMapId);
        glDeleteFramebuffers(1,&frameBuffer);
    }

    void doEffect(){
        //save some stuff in order to restore it when we are done
        Matrix cameraViewMatrix=RenderStrategy::getInstance().getViewMatrix();
        //change to the light's point of view
        Matrix viewMatrix=getViewMatrix();
        RenderStrategy::getInstance().setViewMatrix(viewMatrix);

        glBindFramebuffer(GL_FRAMEBUFFER,frameBuffer);
        glClear(GL_DEPTH_BUFFER_BIT);
        //this is to remove artifacts
        glPolygonOffset(8.0,4.0);
        glEnable(GL_POLYGON_OFFSET_FILL);

        //render the whole world
        vector<Component*> worldChilds=Application::getInstance().getWorld().getChilds();
        for(Component* child:worldChilds){
                if(child->getCastsShadow()){
                    child->render(this->basicShader,this->basicTexture);
                }
        }
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        
        //Restore all the changes
        glDisable(GL_POLYGON_OFFSET_FILL);
        RenderStrategy::getInstance().setViewMatrix(cameraViewMatrix);

        Matrix biasMatrix=getBiasMatrix();
        RenderStrategy::getInstance().setLightViewProjectionMatrix(biasMatrix,viewMatrix);
	}

    //biasMatrix: [-1,1] -> [0,1]
    Matrix getBiasMatrix(){
        Matrix biasMatrix=Matrix(1);
        biasMatrix.translate(0.5,0.5,0.5);
        biasMatrix.scale(0.5,0.5,0.5);
        return biasMatrix;
    }
    //create the light's view matrix
    Matrix getViewMatrix(){
        Point lightA=light->getPosition().getAngular();
        Point lightL=light->getPosition().getLinear();
        Matrix viewMatrix=Matrix(1);
        viewMatrix.rotate(lightA.x, 1.0f, 0.0f, 0.0f);
        viewMatrix.rotate(lightA.y, 0.0f, 1.0f, 0.0f);
        viewMatrix.translate( -lightL.x,-lightL.y,-lightL.z );

        return viewMatrix;
    }
	void undoEffect(){
		//do nothing
	}


};
#endif
