#ifndef PositionH
#define PositionH

class Position {

  protected:    
    float x;
    float y;
    float z;
    float theta;
    float phi;
    float psi;    
    
  public:
        Position(){
            this->x=0;
            this->y=0;
            this->z=0;
            this->phi=0;
            this->theta=0;
            this->psi=0;
        }
        
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
		this->set(x,y,z,this->phi,this->theta,this->psi);
	}
	//TODO:this should ne just in the component	
	void set(float x,float y,float z,float phi,float theta,float psi){
		this->x=x;
		this->y=y;
		this->z=z;
		this->phi=phi;
		this->theta=theta;
		this->psi=psi;
	}

	float setX(float x){
    	this->x=x;
    }

    float setY(float y){
    	this->y=y;
    }    

    float setZ(float z){
    	this->z=z;
    }

    float setPhi(float phi){
    	this->phi=phi;
    }

    float setTheta(float theta){
    	this->theta=theta;
    }    

    float setPsi(float psi){
    	this->psi=psi;
    }

	Position& operator+=(const Position position) {
        this->x+=position.x;
        this->y+=position.y;
        this->z+=position.z;
        this->phi+=position.phi;
        this->theta+=position.theta;
        this->psi+=position.psi;
        return *this;
  	}

    friend std::ostream& operator<<(std::ostream& os , const Position p){
        os << "("<<p.x<<","<< p.y<<","<< p.z<<")"<< "\n";
    }

    float norm(){
        return sqrt((x*x) + (y*y) + (z*z));
    }
  
};

#endif
