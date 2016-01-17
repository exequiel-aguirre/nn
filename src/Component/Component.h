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
#include "../Physics/CollisionStatus.h"


class Component {
 private:
    static constexpr float EARTH_MASS=5.972 * pow(10,24);
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
    bool rotates=false;
    bool moves=false;
    Matrix inertiaInverse;
    bool reflects=true;
    bool collides=true;
    static constexpr const char* DEFAULT_SHADER_NAME="Basic";
    static constexpr const char* DEFAULT_TEXTURE_FILENAME="img/default.bmp";
  public:
    Component(Position position,ModelObject modelObject,const char* textureFilename,GLenum GLMode,const char* shaderName){
      this->position=position;
      this->updateModelMatrix();
      this->modelObject=modelObject;
      this->calculateBoundary();
      this->calculateInertiaInverse();
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

    virtual void render(){
      doEffects();
      RenderStrategy::getInstance().render(this->modelMatrix,this->modelObject,this->shader,this->texture);
      undoEffects();
    }

    virtual void onAfterCollision(){}

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
      modelMatrix.rotate(position.getTheta(),position.getPsi(),position.getPhi());
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
      modelObject.getBoundary().update(modelMatrix,velocity);
    }

    Boundary& getBoundary(){
      return modelObject.getBoundary();
    }

    CollisionStatus& getCollisionStatus(){
      return modelObject.getBoundary().getCollisionStatus();
    }

    Texture& getTexture(){
      return texture;
    }

    Shader& getShader(){
      return shader;
    }

    virtual float getMass(){
      if(modelObject.getSize()==0) return 0;
      if(!this->getMoves()) return EARTH_MASS;//if it's unmovable, we treat it as if it was fixed to the earth
      //a very rough approximation of volume
      return modelObject.getBoundary().getEnclosingBox().getVolume()* massDensity;
    }

    //a very rough approximation of the inertia is used here.
    void calculateInertiaInverse(){
      if(getMass()==0){
        inertiaInverse=Matrix(0.0);
        return;
      }
      Point mm=modelObject.getBoundary().getEnclosingBox().getWHD();
      float m=getMass();
      float xx=mm.x*mm.x;
      float yy=mm.y*mm.y;
      float zz=mm.z*mm.z;

      inertiaInverse=Matrix(m*(yy+zz)/12.0, m*(xx+zz)/12.0, m*(xx+yy)/12.0, 1.0).getInverse();
    }

    virtual Matrix getInertiaInverse(){
      if((getMass()>5e15) || !this->getRotates() ) return Matrix(0.0);
      return inertiaInverse;
    }

    virtual float getElasticity(){
      return elasticity;
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
      this->rotates=rotates;
    }
    bool getRotates(){
      return rotates;
    }

    void setMoves(bool moves){
      this->moves=moves;;
    }
    bool getMoves(){
      return moves;
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
    Component* setCollides(bool collides){
      this->collides=collides;
      return this;
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

