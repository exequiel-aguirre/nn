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
-When 2 objects with std::numeric_limits<float>::max() collide, everything goes to hell (for example, most things just dissapear)
-blending effect not working so well...
- we are setting velocity and acceleration to object with no motion. The objects don't move, but the collision is affected (for example, objects not bounding like they should) 
--bug the ReducedPolygon has some malformed vertices (two or more vertices equals) causin the normal to be zero, causing the distance to be 0 when it's not

TODOS:
-Performance: 
--Maybe Point::rotate should return a Point& instead of (just) Point.
--The animation::render is making a copy of the model object on each call
--Maybe we should update the reduced polygonm, just when we use it.(i.e just before the getSeparation)
-CollisionDetector:
- the rawPoint was created, but now inside point we have duplicated x,y,z. Besides that, if we modify point->x, rawPoint won't change, which I think is fine having in mind that we are using GL_STATIC_DRAW?
-the modelObject should be created in the component and passed to the renderStrategy, not the other way around (?). After putting the modelObject in the component, the animation is bounding against the box (like it should, but it's odd that this change fix that...)
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

if(getModelObject()==NULL) return;
      Point* boundaryMin= getModelObject()->getBoundary()->getEnclosingBox()->getDiagonalMin();
      Point* boundaryMax= getModelObject()->getBoundary()->getEnclosingBox()->getDiagonalMax();
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

and the MOVO vertices and MOVO normals
if(getModelObject()==NULL) return;
      vector<Point*>* vertices=getModelObject()->getBoundary()->getModelObjectVO()->getPositionedVertices();
      vector<Point*>::iterator it;
      glBegin(GL_TRIANGLES);
      for(it=vertices->begin();it!=vertices->end();it++){
          Point* p=(*it);
          glVertex3f(p->x,p->y,p->z);
      }
      glEnd();

      vector<std::pair<Point*,Point*>>* trianglePlanes=getModelObject()->getBoundary()->getModelObjectVO()->getPositionedTrianglePlanes();
      vector<std::pair<Point*,Point*>>::iterator itp;
      glBegin(GL_LINES);
      for(itp=trianglePlanes->begin();itp!=trianglePlanes->end();itp++){
          Point* x0=(*itp).first;
          Point* n=(*itp).second;
          glVertex3f(x0->x,x0->y,x0->z);
          glVertex3f(x0->x+n->x, x0->y+n->y, x0->z+n->z);
      }
      glEnd();