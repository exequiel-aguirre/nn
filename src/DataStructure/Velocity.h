#ifndef VelocityH
#define VelocityH

class Velocity{

  private:    
    float x;
    float y;
    float z;    
    
  public:
  		Velocity(float x,float y,float z){
  			this->x=x;
  			this->y=y;
  			this->z=z;
			
  		}  		
    
    virtual ~Velocity(){}  

    float getX(){
    	return x;
    }

    float getY(){
    	return y;
    }

    float getZ(){
    	return z;
    }

    void set(float x,float y,float z){
        this->x=x;
        this->y=y;
        this->z=z;
    }
    
    void setX(float x){
    	this->x=x;
    }

    void setY(float y){
    	this->y=y;
    }    

    void setZ(float z){
    	this->z=z;
    }
  
};

#endif
