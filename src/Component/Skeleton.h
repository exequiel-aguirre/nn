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
      Joint* joint=new Joint(rawJoint.id,Position(rawJoint.actions[0].position.x,rawJoint.actions[0].position.y,rawJoint.actions[0].position.z));
      for(RawAction& rawAction:rawJoint.actions){
        joint->addAction(rawAction.position,rawAction.duration);
      }
      joints.push_back(joint);
    }
    updateJointsPosition(position.getLinear());

    for(RawBone rawBone:rawSkeleton.bones){
      Joint* jointA=findJointById(rawBone.aId);
      Joint* jointB=findJointById(rawBone.bId);
      Bone* bone=new Bone(Position(0,0,0),jointA,jointB);
      bones.push_back(bone);
    }
  }

  void updateJointsPosition(Point deltaPosition){
    for(Joint* joint:joints){
      Point position=joint->getPosition().getLinear();
      position=position+deltaPosition;
      joint->setPosition(position.x,position.y,position.z);

      std::vector<Action>& actions=joint->getActions();
      for(Action& action:actions){
        action.position=action.position+deltaPosition;
      }
    }
  }

  void render(){
    for(Joint* joint: joints){
      joint->render();
    }

    for(Bone* bone: bones){
      bone->render();
    }
  }

  void setPosition(float x,float y,float z,float phi,float theta,float psi){
    Point deltaPosition=Point(x,y,z)-position.getLinear();
    Component::setPosition(x,y,z,phi,theta,psi);
    updateJointsPosition(deltaPosition);
  }

  Joint* findJointById(unsigned int id){
    auto it=std::find_if(joints.begin(),joints.end(),
              [id](Joint* joint){ return (joint->getId()==id); });
    return (*it);
  }
  


    //TODO:this is just for debug
    void reload(){
      joints.clear();
      bones.clear();
      RawSkeleton rawSkeleton=Utils::loadSkeleton("animation/walk.ani");
      buildJointsAndBones(rawSkeleton);    
  }

};
#endif
