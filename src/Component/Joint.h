#ifndef JointH
#define JointH

#include "Sphere.h"

//TODO:find a better name
struct Action{
    Point position;//this position is relative to the skeleton
    float deltaT;
};

class Joint: public Sphere {
  private:
    unsigned int id;
    vector<Action> actions;
    unsigned int currentActionIndex;
    float t;
    Matrix skeletonModelMatrix;
    static constexpr float R=0.1;

  public:
	Joint(unsigned int id,Position&& position):Sphere(std::move(position),R,"img/default.bmp"){
        this->id=id;
        this->currentActionIndex=0;
        this->t=0;
    }

    void render(){
        this->animate();
        Sphere::render();
    }
    
    void animate(){
        if(actions.empty()) return;

        if(t>1){
            currentActionIndex=(currentActionIndex+1) % actions.size();
            t=0;
        }
        Action action=actions[currentActionIndex];
        Action nextAction=actions[(currentActionIndex+1) % actions.size()];

        t+=action.deltaT;
        Point p= (1.0-t)*action.position + t*nextAction.position;
        p=skeletonModelMatrix* p;
        this->setPosition(p.x,p.y,p.z);
    }
      
    unsigned int getId(){
      return this->id;
    }
    Joint* addAction(Point position,float duration){
        Action action;
        action.position=position;
        action.deltaT=1.0/(60*duration);
        actions.push_back(action);

        return this;
    }

    void setSkeletonPosition(Matrix skeletonModelMatrix){
        this->skeletonModelMatrix=skeletonModelMatrix;
    }

};


#endif
