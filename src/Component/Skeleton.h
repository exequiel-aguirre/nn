#ifndef SkeletonH
#define SkeletonH
#include "Component.h"
#include "Joint.h"
#include "Bone.h"
#include <vector>
#include "../Utils/Utils.h"
//just  for debug
#include "../Behavior/SimpleKeyboardBehavior.h"

class Skeleton: public Component {
  private:
    vector<Joint*> joints;
    vector<Bone*> bones;
    unsigned int frames=0;
  public:
  using Component::add;//just for debug
  Skeleton(Position& position,const char* filename):Component(position){
    RawSkeleton rawSkeleton=Utils::loadSkeleton(filename);
    buildJointsAndBones(rawSkeleton);

    //Create the skeleton modelObject by merging joint's modelObjects.
    for(Joint* joint:joints){
      this->modelObject.merge(joint->getModelObject(),this->modelMatrix.getInverse()*joint->getModelMatrix());//Joints already have their positions added to the skeletons, so we need to undo this with the inverse
    }    
    this->calculateBoundary();

    //TODO:just for debug
     add(new SimpleKeyboardBehavior(
              [=](SDL_Keycode key){//behavior callback
                if(key== SDLK_r) this->reload();
                if(key== SDLK_c) this->nextCycle();
              },
              [=](SDL_Keycode key){//behavior callback
                
              }
          ));
  }

  Skeleton(Position&& position,const char* filename):Skeleton(position,filename){};

  ~Skeleton(){
    for(Bone* bone:bones){
        delete(bone);
    }
    for(Joint* joint:joints){
        delete(joint);
    }
  }

  void buildJointsAndBones(RawSkeleton& rawSkeleton){
    for(RawJoint& rawJoint: rawSkeleton.joints){
      Point jointPosition=modelMatrix * rawJoint.cycles[0].actions[0].position;
      Joint* joint=new Joint(rawJoint.id,Position(jointPosition.x,jointPosition.y,jointPosition.z),rawJoint.r);
      for(RawCycle rawCycle:rawJoint.cycles){
          joint->addCycle(rawCycle);
      }
      joints.push_back(joint);
    }
    //onPositionChanged();//I think this is not needed. But not sure about that...

    for(RawBone rawBone:rawSkeleton.bones){
      Joint* jointA=findJointById(rawBone.aId);
      Joint* jointB=findJointById(rawBone.bId);
      Bone* bone=new Bone(Position(0,0,0),jointA,jointB);
      bones.push_back(bone);
    }
  }

  void onPositionChanged(){
    for(Joint* joint:joints){
      joint->setSkeletonPosition(modelMatrix);
    }
  }

  void render(){
    if(frames++ >1) frames=0;

    for(Joint* joint: joints){
      if(frames==0) joint->animate();
      joint->render();
    }

    for(Bone* bone: bones){
      if(frames==0) bone->animate();
      bone->render();
    }
  }

  void setPosition(float x,float y,float z,float phi,float theta,float psi){
    Component::setPosition(x,y,z,phi,theta,psi);
    onPositionChanged();
  }

  Joint* findJointById(std::string id){
    auto it=std::find_if(joints.begin(),joints.end(),
              [id](Joint* joint){ return (joint->getId().compare(id)==0 ); });
    return (*it);
  }
  


    //TODO:this is just for debug
    void reload(){
      joints.clear();
      bones.clear();
      RawSkeleton rawSkeleton=Utils::loadSkeleton("animation/skeleton.ani");
      buildJointsAndBones(rawSkeleton);
      onPositionChanged();
  }
  void nextCycle(){
    for(Joint* joint:joints){
      joint->nextCycle();
    }
  }

};
#endif
