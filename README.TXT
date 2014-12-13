//install environment
>apt-get install build-essential mesa-common-dev libsdl2-dev libglew-dev

To compile:
>g++ src/main.cpp -std=c++11 -w -lGL  -lSDL2 -lGLEW


// glut was not used, but in that case it would be...
>apt-get install build-essential mesa-common-dev libsdl2-dev freeglut3-dev
>g++ src/main.cpp -w  -lglut -lGL -lGLU  -lSDL2

DEBUG:
>gdb ./a.out
>r
>bt full

PROFILE:
>g++ src/main.cpp -w  -lGL  -lSDL2 -pg;./a.out 
>gprof > r.txt
>kate r.txt

ANIMATION:
-install blender and the latest stable version of makehuman.Install blender's makehuman plugin by downloading them and coping those folder to ~/.config/blender/2.69/scripts/addons/
-open makehuman and export the default to the blender exchange format
-open blender and load the previous exported file with scale 0.3
-with the makewalk plugin , "load and retarget" /usr/share/makehuman/data/bvhs/02_02.bvh and set max frames to 60(23 or whatever)
-select human:body on the right hierachy and click the wrench, add a modifier decimate to 0.01 (same to human:tshirt, human:jeans, etc)
-now select human(top one) on the right and with "makewalk:edit actions" on the left, click global edit and fixate location. (if you select a frame where the human is in the center of the action you will fixate it there.(which is the intended))
-export as obj ticking export include normal,include uvs,triangulate faces,animation,apply modifiers,objects as OBJ objects. (the first three are for any model whatsoever)

BUGS:
-blending effect not working so well...
-Position::set() not working when zero value is passed. (here NULL=0)

TODOS:
-CollisionDetector:
--the ModelObjectVO::buildPositionedVertices is a big memory leak. Maybe using deltaPosition can solve the problem (we would use a rotate instead of rotateCopy)
--bug if normalize receive a point such that ||p||=0 it returns the same point, causing corruption.(also the vertices are reapeting points....)
--if the velocity and acceleration is 0 do not calculate distance (or collision alltogether)
--remove all static
- create an struct RawPoint, and put all the point logic that is on utils in the Point class.(add a method Point->getRawPoint to be added in the ModelObject)
-all the collide(), setCollide should be done within the component
-check why the performance decreased so much by the new box.
---most likely because it's render each component separately.We could implement some merge method, that agregates each component in the same modelobject and render it as a whole.
-implement a factory so we can avoid thius chaotics constructors
-add a getNormals to creasedDecorator
-make TextureStrategy and AnimatonStrategy a decorator, so we could call something like
	new Animation(new TexturureStrategy(new CacheStrategy(modelFilename),textureFilename))(?)
-try template for ciclyc reference.
-remove all warnings

Notes:
-To see the diagonals the collisionDetector use, put this at the end of Component::afterRender
	if(boundaryMin==NULL) return;
	      glBegin(GL_LINES);
	        glVertex3f(boundaryMin->x,boundaryMin->y,boundaryMin->z);
	        glVertex3f(boundaryMax->x,boundaryMax->y,boundaryMax->z);
	      glEnd();


or the whole box

if(boundaryMin==NULL) return;
        glBegin(GL_LINES);

          //front rectangle
          glVertex3f(boundaryMin->x,boundaryMin->y,boundaryMin->z);
          glVertex3f(boundaryMax->x,boundaryMin->y,boundaryMin->z);

          glVertex3f(boundaryMax->x,boundaryMin->y,boundaryMin->z);
          glVertex3f(boundaryMax->x,boundaryMax->y,boundaryMin->z);

          glVertex3f(boundaryMax->x,boundaryMax->y,boundaryMin->z);
          glVertex3f(boundaryMin->x,boundaryMax->y,boundaryMin->z);

          glVertex3f(boundaryMin->x,boundaryMax->y,boundaryMin->z);
          glVertex3f(boundaryMin->x,boundaryMin->y,boundaryMin->z);


          //back rectangle
          glVertex3f(boundaryMin->x,boundaryMin->y,boundaryMax->z);
          glVertex3f(boundaryMax->x,boundaryMin->y,boundaryMax->z);

          glVertex3f(boundaryMax->x,boundaryMin->y,boundaryMax->z);
          glVertex3f(boundaryMax->x,boundaryMax->y,boundaryMax->z);

          glVertex3f(boundaryMax->x,boundaryMax->y,boundaryMax->z);
          glVertex3f(boundaryMin->x,boundaryMax->y,boundaryMax->z);

          glVertex3f(boundaryMin->x,boundaryMax->y,boundaryMax->z);
          glVertex3f(boundaryMin->x,boundaryMin->y,boundaryMax->z);

          //depth rectangle
          glVertex3f(boundaryMin->x,boundaryMin->y,boundaryMin->z);
          glVertex3f(boundaryMin->x,boundaryMin->y,boundaryMax->z);

          glVertex3f(boundaryMax->x,boundaryMin->y,boundaryMin->z);
          glVertex3f(boundaryMax->x,boundaryMin->y,boundaryMax->z);

          glVertex3f(boundaryMax->x,boundaryMax->y,boundaryMin->z);
          glVertex3f(boundaryMax->x,boundaryMax->y,boundaryMax->z);

          glVertex3f(boundaryMin->x,boundaryMax->y,boundaryMin->z);
          glVertex3f(boundaryMin->x,boundaryMax->y,boundaryMax->z);

          
        glEnd();
