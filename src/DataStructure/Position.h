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
    
  public:
  		Position(float relativeX,float relativeY,float relativeZ,float relativeTheta,float relativePhi,float relativePsi){
  			this->parent=NULL;
			this->relativeX=relativeX;
			this->relativeY=relativeY;
			this->relativeZ=relativeZ;
			this->relativeTheta=relativeTheta;
			this->relativePhi=relativePhi;
			this->relativePsi=relativePsi;
  		} 		
  		
		Position(float relativeX,float relativeY,float relativeZ,float relativeTheta,float relativePhi):Position(relativeX,relativeY,relativeZ,relativeTheta,relativePhi,0.0f){}
		Position(float relativeX,float relativeY,float relativeZ):Position(relativeX,relativeY,relativeZ,0.0f,0.0f,0.0f){}
		
    
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
	void set(float x,float y,float z){
		this->relativeX=x;
		this->relativeY=y;
		this->relativeZ=z;
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
  
};

#endif
