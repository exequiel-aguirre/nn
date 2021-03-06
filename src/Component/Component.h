#ifndef ComponentH
#define ComponentH
#include <vector>
#include "../DataStructure/Matrix.h"
#include "../DataStructure/Position.h"
#include "../DataStructure/Velocity.h"
#include "../DataStructure/Acceleration.h"
#include "../Behavior/IBehavior.h"
#include "../Listener/ListenerManager.h"
#include "../Effect/IEffect.h"
#include "../DataStructure/ModelObject.h"
#include "../RenderStrategy/RenderStrategy.h"
#include "../RenderStrategy/ResourceManager.h"
#include "../RenderStrategy/Shader/Shader.h"
#include "../RenderStrategy/Texture.h"
#include "../Physics/ContactInfo.h"


class Component {
  protected:
    ModelObject modelObject;
    Matrix modelMatrix;
    Shader shader;
    Texture texture;
    vector<IEffect*> effects;

    vector<IBehavior*> behaviors;
    //mechanic properties
    Position position;
    Velocity velocity;
    Acceleration acceleration;
    float massDensity=1.0f;
    float elasticity=0.0f;
    float friction=0.5f;
    float massInverse=0.0f;
    Matrix inertiaInverse;
    bool reflects=true;
    bool castsShadow=true;
    bool collides=true;
    unsigned int sleepingFrames=0;
    static constexpr unsigned int SLEEPING_FRAMES=60*2;
    static constexpr const char* DEFAULT_SHADER_NAME="Default";
    static constexpr const char* DEFAULT_TEXTURE_FILENAME="img/default.bmp";
  public:
    Component(Position position,ModelObject modelObject,const char* textureFilename,GLenum GLMode,const char* shaderName){
      this->position=position;
      this->updateModelMatrix();
      this->modelObject=modelObject;
      this->calculateBoundary();
      RenderStrategy::getInstance().initModelObject(this->modelObject,GLMode);
      if(shaderName==NULL) shaderName=DEFAULT_SHADER_NAME;
      this->shader=ResourceManager::getInstance().getShader(shaderName);
      if(textureFilename==NULL) textureFilename=DEFAULT_TEXTURE_FILENAME;
      this->texture=ResourceManager::getInstance().getTexture(textureFilename);
    }

    Component(Position position,ModelObject modelObject,const char* textureFilename,GLenum GLMode):Component(position,modelObject,textureFilename,GLMode,NULL){}
    Component(Position position,ModelObject modelObject,GLenum GLMode):Component(position,modelObject,NULL,GLMode,NULL){}
    Component(Position position):Component(position,ModelObject(),NULL,GL_POINTS,NULL){}//by default we set a render strategy with an empty model object, so no geometry will be rendered)(the GLMode is never actually used)

    virtual ~Component(){}  
    
    //this method is called before any component is rendered.
    virtual void onBeforeRenderFrame(){}
    //this method is called before the collision detection starts
    virtual void onBeforeDetectCollision(){}
    //this method is called every time a collision is detected
    virtual void onCollisionDetected(ContactInfo contactInfo){}

    virtual void render(){
      doEffects();
      RenderStrategy::getInstance().render(this->modelMatrix,this->modelObject,this->shader,this->texture);
      undoEffects();
    }
    //This is just for performance when rendering shadows
    virtual void render(Shader& shader,Texture& texture){
      RenderStrategy::getInstance().render(this->modelMatrix,this->modelObject,shader,texture);
    }

    Position& getPosition(){
      return position;
    }

    void setPosition(float x,float y,float z){
      this->setPosition(x,y,z,position.getPhi(),position.getTheta(),position.getPsi());
    }
    virtual void setPosition(float x,float y,float z,float phi,float theta,float psi){
      this->position.set(x,y,z,phi,theta,psi);
      updateModelMatrix();
      //position changes so boundaries change
      calculateBoundary();
    }

    void updateModelMatrix(){
      modelMatrix.loadIdentity();
      modelMatrix.translate(position.getX(),position.getY(),position.getZ());
      modelMatrix.rotate(position.getPhi(),position.getTheta(),position.getPsi());
    }
    
    Matrix& getModelMatrix(){
      return modelMatrix;
    }

    Velocity& getVelocity(){
      return velocity;
    }
    void setVelocity(float x,float y,float z){
      this->velocity.set(x,y,z);
    }
    void setVelocity(float x,float y,float z,float phi,float theta,float psi){
      this->velocity.set(x,y,z,phi,theta,psi);
    }
    
    Acceleration& getAcceleration(){
      return acceleration;
    }
    void setAcceleration(float x,float y,float z){
      this->acceleration.set(x,y,z);
    }
    void setAcceleration(float x,float y,float z,float phi,float theta,float psi){
      this->acceleration.set(x,y,z,phi,theta,psi);
    }
    
    ModelObject& getModelObject(){
      return modelObject;
    }


    virtual void calculateBoundary(){
      if(modelObject.getSize()==0) return;
      //update the boundary
      modelObject.getBoundary().update(modelMatrix);
    }

    Boundary& getBoundary(){
      return modelObject.getBoundary();
    }

    Texture& getTexture(){
      return texture;
    }

    Shader& getShader(){
      return shader;
    }

    float getMassInverse(){
      return massInverse;
    }

    Matrix getInertiaInverse(){
      return inertiaInverse;
    }

    float getElasticity(){
      return elasticity;
    }

    float getFriction(){
      return friction;
    }

    Component* add(IBehavior* behavior){
      behavior->bind(this);
      this->behaviors.push_back(behavior);
      ListenerManager::getInstance().add(behavior);
      return this;
    
    }

    Component* add(IEffect* effect){
      this->effects.push_back(effect);
      return this;    
    }

    void setRotates(bool rotates){
      if(rotates){
        if(getMassInverse()==0){
          inertiaInverse=Matrix(0.0);
          return;
        }
        //a very rough approximation of the inertia is used here.
        Point mm=modelObject.getBoundary().getEnclosingBox().getWHD();
        float m=1.0/getMassInverse();
        float xx=mm.x*mm.x;
        float yy=mm.y*mm.y;
        float zz=mm.z*mm.z;
        inertiaInverse=Matrix(m*(yy+zz)/12.0, m*(xx+zz)/12.0, m*(xx+yy)/12.0, 1.0).getInverse();
      }
      else
      {
        inertiaInverse=Matrix(0.0);
      }
    }

    void setTranslates(bool translates){
      if(translates){
        //a very rough approximation of volume
        massInverse=1.0/(modelObject.getBoundary().getEnclosingBox().getVolume()* massDensity);
      }
      else
      {
        massInverse=0.0;
      }
    }

    Component* setReflects(bool reflects){
      this->reflects=reflects;
      return this;
    }
    bool getReflects(){
      return reflects;
    }
    bool getCollides(){
      return collides;
    }
    Component* setCastsShadow(bool castsShadow){
      this->castsShadow=castsShadow;
      return this;
    }
    bool getCastsShadow(){
      return castsShadow;
    }
    Component* setCollides(bool collides){
      this->collides=collides;
      return this;
    }
    //TODO:this whole sleeping logic should be in the boundary
    bool isSleeping(){
      if(massInverse==0 && inertiaInverse[15]==0) return true;
      return sleepingFrames>SLEEPING_FRAMES;
    }
    void incrementSleepingFrames(){
      if(sleepingFrames<=SLEEPING_FRAMES) sleepingFrames++;//increment the sleeping frames, unless we already match the condition
    }
    void wakeUp(){
      sleepingFrames=0;
    }

    void doEffects(){
      vector<IEffect*>::iterator it;

      for(it=effects.begin();it!=effects.end();it++)
      {
          (*it)->doEffect();
      }
    }

    void undoEffects(){
      vector<IEffect*>::iterator it;

      for(it=effects.begin();it!=effects.end();it++)
      {
          (*it)->undoEffect();
      }
    }

};
#endif

