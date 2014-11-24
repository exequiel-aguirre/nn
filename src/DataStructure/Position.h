#ifndef PositionH
#define PositionH
//TODO:change the name to something like "state"
class Position {

  private:
    Position* parent;
    float relativeX;
    float relativeY;
    float relativeZ;
    float relativeTheta;
    float relativePhi;
    float relativePsi;
    //mechanic properties
    float velocity=0;
    float acceleration=0;
    
  public:
  		Position(float relativeX,float relativeY,float relativeZ,float relativeTheta,float relativePhi,float relativePsi,float velocity, float acceleration){
  			this->parent=NULL;
			this->relativeX=relativeX;
			this->relativeY=relativeY;
			this->relativeZ=relativeZ;
			this->relativeTheta=relativeTheta;
			this->relativePhi=relativePhi;
			this->relativePsi=relativePsi;			
			this->velocity=velocity;
			this->acceleration=acceleration;
  		} 		
  		Position(float relativeX,float relativeY,float relativeZ,float relativeTheta,float relativePhi,float relativePsi):Position(relativeX,relativeY,relativeZ,relativeTheta,relativePhi,relativePsi,0.0f,0.0f){}
		Position(float relativeX,float relativeY,float relativeZ,float relativeTheta,float relativePhi):Position(relativeX,relativeY,relativeZ,relativeTheta,relativePhi,0.0f,0.0f,0.0f){}
		Position(float relativeX,float relativeY,float relativeZ):Position(relativeX,relativeY,relativeZ,0.0f,0.0f,0.0f,0.0f,0.0f){}
		
    
    virtual ~Position(){}  
    
    void setParent(Position* parent){
      this->parent=parent;
    }

      	
    float getRelativeX(){			
			return this->relativeX;		
		}		
	
    float getRelativeY(){			
			return this->relativeY;		
		}		
	
    float getRelativeZ(){	
			return this->relativeZ ;		
		}
	
    float getRelativeTheta(){			
			return this->relativeTheta;
		}		
		
    float getRelativePhi(){		
			return this->relativePhi;
		}

	float getRelativePsi(){		
			return this->relativePsi;
		}
	//TODO:this should ne just in the component	
	void move(float deltaX,float deltaY,float deltaZ){
		this->relativeX+=deltaX;
		this->relativeY+=deltaY;
		this->relativeZ+=deltaZ;
	}
    //decorate this method in order to achive the relative pos.
    float getAbsoluteX(){
			if(parent==NULL) return this->relativeX;
			return this->relativeX + parent->getAbsoluteX();			
		}
		
		//decorate this method in order to achive the relative pos.
    float getAbsoluteY(){
			if(parent==NULL) return this->relativeY;
			return this->relativeY + parent->getAbsoluteY();			
		}
		
		//decorate this method in order to achive the relative pos.
    float getAbsoluteZ(){
			if(parent==NULL) return this->relativeZ;
			return this->relativeZ + parent->getAbsoluteZ();			
		}


	//decorate this method in order to achive the relative theta.
    float getAbsoluteTheta(){
			if(parent==NULL) return this->relativeTheta;
			return this->relativeTheta + parent->getAbsoluteTheta();			
		}
		
		//decorate this method in order to achive the relative phi.
    float getAbsolutePhi(){
			if(parent==NULL) return this->relativePhi;
			return this->relativePhi + parent->getAbsolutePhi();			
		}
	
	//decorate this method in order to achive the relative phi.
	float getAbsolutePsi(){
			if(parent==NULL) return this->relativePsi;
			return this->relativePsi + parent->getAbsolutePsi();			
		}

	void setVelocity(float velocity){
		this->velocity=velocity;
	}
	float getVelocity(){
		return this->velocity;
	}
	float getAcceleration(){
		return this->acceleration;
	}
  
};

#endif
