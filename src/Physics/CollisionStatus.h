#ifndef CollisionStatusH
#define CollisionStatusH


class CollisionStatus{
  private:
    //this is the intersection segment length (how bad the crash was...)
    float islx=0.0f;
    float isly=0.0f;
    float islz=0.0f;
    //where was I when the collision happened
    bool xMin=false;
    bool xMax=false;
    bool yMin=false;
    bool yMax=false;
    bool zMin=false;
    bool zMax=false;
  public:
    CollisionStatus(){
        init();
    }
    virtual ~CollisionStatus(){}
    
    bool hasCollided(){
        return (xMin || xMax || yMin || yMax || zMin || zMax);
    }

    void init(){
        islx=0.0f;
        isly=0.0f;
        islz=0.0f;
        xMin=false;
        xMax=false;
        yMin=false;
        yMax=false;
        zMin=false;
        zMax=false;
    }
    
    void set(float islx,float isly,float islz,bool xMin,bool xMax,bool yMin,bool yMax,bool zMin ,bool zMax){
        this->islx=islx;
        this->isly=isly;
        this->islz=islz;
        if(xMin) this->xMin=xMin;
        if(xMax) this->xMax=xMax;
        if(yMin) this->yMin=yMin;
        if(yMax) this->yMax=yMax;
        if(zMin) this->zMin=zMin;
        if(zMax) this->zMax=zMax;
    }

    float getIslx(){
        return islx;
    }
    float getIsly(){
        return isly;
    }
    float getIslz(){
        return islz;
    }
    bool getXMin(){
        return this->xMin;
    }
    bool getXMax(){
        return this->xMax;
    }

    bool getYMin(){
        return this->yMin;
    }
    bool getYMax(){
        return this->yMax;
    }

    bool getZMin(){
        return this->zMin;
    }
    bool getZMax(){
        return this->zMax;
    }

};
#endif
