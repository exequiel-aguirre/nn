#ifndef PositionH
#define PositionH

class Position {

  private:
    Position* parent;
    float relativeX;
    float relativeY;
    float relativeZ;
    float relativeTheta;
    float relativePhi;
    
  public:
  		Position(float relativeX,float relativeY,float relativeZ,float relativeTheta,float relativePhi ){
  			this->parent=NULL;
			this->relativeX=relativeX;
			this->relativeY=relativeY;
			this->relativeZ=relativeZ;
			this->relativeTheta=relativeTheta;
			this->relativePhi=relativePhi;
  		}
		Position(float relativeX,float relativeY,float relativeZ):Position(relativeX,relativeY,relativeZ,0.0f,0.0f){}
    
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
  
};

#endif
