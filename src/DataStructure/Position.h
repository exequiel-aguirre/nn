#ifndef PositionH
#define PositionH

class Position {

  private:    
    float x;
    float y;
    float z;
    float theta;
    float phi;
    float psi;    
    
  public:
  		Position(float x,float y,float z,float phi,float theta,float psi){  			
			this->x=x;
			this->y=y;
			this->z=z;
			this->phi=phi;
			this->theta=theta;
			this->psi=psi;
  		} 		
  		
		Position(float x,float y,float z,float phi,float theta):Position(x,y,z,phi,theta,0.0f){}
		Position(float x,float y,float z):Position(x,y,z,0.0f,0.0f,0.0f){}
		
    
    virtual ~Position(){}  
              	
    float getX(){			
			return this->x;		
		}		
	
    float getY(){			
			return this->y;		
		}		
	
    float getZ(){	
			return this->z ;		
		}
	
	float getPhi(){		
			return this->phi;
		}

    float getTheta(){			
			return this->theta;
		}			
    
	float getPsi(){		
			return this->psi;
		}

	void set(float x,float y,float z){
		this->set(x,y,z,NULL,NULL,NULL);
	}
	//TODO:this should ne just in the component	
	void set(float x,float y,float z,float phi,float theta,float psi){
		if(x!=NULL) this->x=x;
		if(y!=NULL) this->y=y;
		if(z!=NULL) this->z=z;
		if(phi!=NULL) this->phi=phi;
		if(theta!=NULL) this->theta=theta;
		if(psi!=NULL) this->psi=psi;
	}    

	Position* operator+=(const Position* position) {
    	this->x+=position->x;
    	this->y+=position->y;
    	this->z+=position->z;
    	this->phi+=position->phi;
    	this->theta+=position->theta;
    	this->psi+=position->psi;
    	return this;
  	}
  
};

#endif
