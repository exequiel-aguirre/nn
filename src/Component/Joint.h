#ifndef JointH
#define JointH

#include "Sphere.h"

//TODO:find a better name
struct Action{
    Point position;//this position is relative to the skeleton
    float deltaT;
};
struct Cycle{
    std::string id;
    std::vector<Action> actions;
};

class Joint: public Sphere {
  private:
    std::string id;
    vector<Cycle> cycles;
    unsigned int currentCycleIndex;
    unsigned int currentActionIndex;
    float t;
    Matrix skeletonModelMatrix;

  public:
	Joint(std::string id,Position&& position,float r):Sphere(std::move(position),r,"img/default.bmp"){
        this->id=id;
        this->currentCycleIndex=0;
        this->currentActionIndex=0;
        this->t=0;
    }

    void render(){
        Sphere::render();
    }
    
    void animate(){
        if(cycles[currentCycleIndex].actions.empty()) return;

        if(t>1){
            currentActionIndex=(currentActionIndex+1) % cycles[currentCycleIndex].actions.size();
            t=0;
        }
        Action action=cycles[currentCycleIndex].actions[currentActionIndex];
        Action nextAction=cycles[currentCycleIndex].actions[(currentActionIndex+1) % cycles[currentCycleIndex].actions.size()];

        t+=action.deltaT;
        Point p= (1.0-t)*action.position + t*nextAction.position;
        p=skeletonModelMatrix* p;
        this->setPosition(p.x,p.y,p.z);
    }
      
    std::string getId(){
      return this->id;
    }
    Joint* addCycle(RawCycle rawCycle){
        Cycle cycle;
        cycle.id=rawCycle.id;
        for(RawAction rawAction:rawCycle.actions){
            Action action;
            action.position=rawAction.position;
            action.deltaT=1.0/(60* rawAction.duration);
            cycle.actions.push_back(action);
        }
        cycles.push_back(cycle);

        return this;
    }

    void setSkeletonPosition(Matrix skeletonModelMatrix){
        this->skeletonModelMatrix=skeletonModelMatrix;
    }


    void nextCycle(){
        currentCycleIndex=(currentCycleIndex+1) % cycles.size();
        currentActionIndex=0;
    }
};


#endif
