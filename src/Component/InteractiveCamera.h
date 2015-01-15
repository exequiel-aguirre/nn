#ifndef InteractiveCameraH
#define InteractiveCameraH

#include "Camera.h"
#include "Cylinder.h"


class InteractiveCamera: public Camera {
  private:
  	Component component=Cylinder(Position(1.0f,-1.0f,-4.0f,90.0f,0.0f,0.0f),0.1f,2.0,"img/wood.bmp");
  public:
	  InteractiveCamera(Position position):Camera(position,false){}

    virtual ~InteractiveCamera(){}

    void onBeforeRenderFrame(){
        glPushMatrix();        
        glLoadIdentity();
        component.onBeforeRender();        
        component.render();
        component.onAfterRender();
        glPopMatrix();

        Camera::onBeforeRenderFrame();
    }   

};


#endif
