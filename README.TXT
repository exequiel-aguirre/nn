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

BLENDER BACKGROUND JOBS:
-open blender, remove camera,light and the cube and press ctrl+u, to save an empty scene as default
>blender --background  --python src/script/join.py -- 3DModel/human_6.obj

-Make the default "open with" for the obj with
>blender --python src/script/import_obj.py --


BUGS:
-add a getNormals to creasedDecorator. This is causing the water's reduced polygon to be a plane.
--Maybe we can use the same approach than in the heightMap
-The skybox isn't working so well, it's obvious that is a box. Also we should be using just a Box with the textures, but with all the rotation needed(see comment on the skybox) the normals get messed up
-The background needs to be the first component to call the onBeforeRenderFrame....
-When 2 objects with std::numeric_limits<float>::max() collide, everything goes to hell (for example, most things just dissapear)
-blending effect not working so well...


TODOS:
-Change the sign in the camera for the angles as well (and swap the order of the rotates)(should be the exact opposite of the Component::onBeforeRender)

-Performance: 
--The animation::render is making a copy of the model object on each call
--CollisionDetector:
--- put if(float d1>EPSILON) just before the willIntersect call. (d1 is cheaper than the willIntersect)
---calculate (b-a) just once
--update reduced polygon on demand: add a flag isUpToDate=(this->position==position) on the ReducedPolygon::update
-CollisionDetector:
- Maybe we should use t instead of d, to detect a collision. (instead of (d<EPSILON) (t<1.0/60.0))
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
-Weird bug,
	Program received signal SIGSEGV, Segmentation fault.
	0x0804a86e in ListenerManager::callMouseListeners (this=0x81fabe0, button=...) at src/Server/../Application/../Listener/ListenerManager.h:33
	33              (*it)->onMouseButtonDown(button);

	This just happens if the the ball's motionBehavior was the 17's element in the vector.
	The solution was to reserve more places in the vector on the constructor.
	Most likely, this happens when the vector needs to resize.

