#ifndef JointH
#define JointH

#include "Sphere.h"

//TODO:find a better name
struct Action{
    Point start;
    Point end;
    float deltaT;
};

class Joint: public Sphere {
  private:
    unsigned int id;
    vector<Action> actions;
    unsigned int currentActionIndex;
    float t;
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

        t+=action.deltaT;
        Point p= (1.0-t)*action.start + t*action.end;
        this->setPosition(p.x,p.y,p.z);
    }
      
    unsigned int getId(){
      return this->id;
    }
    Joint* addAction(Point start,Point end,float duration){
        Action action;
        action.start=start;
        action.end=end;
        action.deltaT=1.0/(60*duration);
        actions.push_back(action);

        return this;
    }


};


#endif
