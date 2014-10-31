#ifndef PositionH
#define PositionH

class Position {

  private:
    Position* parent;
    float relativeX;
    float relativeY;
    float relativeZ;
    
  public:
		Position(float relativeX,float relativeY,float relativeZ){
      this->parent=NULL;
			this->relativeX=relativeX;
			this->relativeY=relativeY;
			this->relativeZ=relativeZ;
		}
    
    virtual ~Position(){}  
    
    void setParent(Position* parent){
      this->parent=parent;
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
  
};

#endif
