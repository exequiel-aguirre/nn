#ifndef CollisionStatusH
#define CollisionStatusH


class CollisionStatus{
  private:
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
        //this->set(false,false,false,false,false,false);
        xMin=false;
        xMax=false;
        yMin=false;
        yMax=false;
        zMin=false;
        zMax=false;
    }
    
    void set(bool xMin,bool xMax,bool yMin,bool yMax,bool zMin ,bool zMax){
        if(xMin) this->xMin=xMin;
        if(xMax) this->xMax=xMax;
        if(yMin) this->yMin=yMin;
        if(yMax) this->yMax=yMax;
        if(zMin) this->zMin=zMin;
        if(zMax) this->zMax=zMax;
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
