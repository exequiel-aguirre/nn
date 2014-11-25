#ifndef AccelerationH
#define AccelerationH

class Acceleration{

  private:    
    float x;
    float y;
    float z;    
    
  public:
  		Acceleration(float x,float y,float z){
  			this->x=x;
  			this->y=y;
  			this->z=z;
			
  		}  		
    
    virtual ~Acceleration(){}  

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
    
    float setX(float x){
    	this->x=x;
    }

    float setY(float y){
    	this->y=y;
    }    

    float setZ(float z){
    	this->z=z;
    }
  
};

#endif
