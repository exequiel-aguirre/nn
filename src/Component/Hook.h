#ifndef HookH
#define HookH

#include "Surface.h"
#include "../Map/EllipsoidMap.h"



class Hook: public Surface {
  private:
	std::function<void(ContactInfo)> onCollisionCallback;
  public:
    
    Hook(Position&& position,float r,const char* textureFilename,std::function<void(ContactInfo)> onCollisionCallback):Surface(position,EllipsoidMap(r,r,r),textureFilename){
        this->onCollisionCallback=onCollisionCallback;
    }
    void onCollisionDetected(ContactInfo contactInfo){
      if(contactInfo.hasCollided) this->onCollisionCallback(contactInfo);
    }
};


#endif
