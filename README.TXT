//install environment
>apt-get install build-essential mesa-common-dev libsdl2-dev libglew-dev

To compile:
>g++ src/main.cpp -w   -lGL  -lSDL2 -lGLEW


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

TODOS:
-check why the performance decreased so much by the new box.
---most likely because it's render each component separately.We could implement some merge method, that agregates each component in the same modelobject and render it as a whole.
-remove all warnings
-BIG ONE:Add a collision detector
--iterate over the objects (that changed the position?) and check if (b->getX-minvertx<a->getx<b->getX+minvertx) || (a->getX-minvertx<b->getx<a->getX+minvertx) && (same for y and z)
---within the setPostion set isChanged to true and on afterrender set it to false.
-refactor the position.Remove all absolute/relative. Leave just x,y,z and overload the + operator.(?)
--or at least change the interface and make the set position to private and allow a move(deltaX,deltaY...) that just changes the relative
-add a getNormals to creasedDecorator

--check if we can save the object with the position in the buffer and do the posioning thing just when it change(the isChanged can be set inside the setPositionMethod.)(?)
--in the component implement a getAbsolutePosition which would be,this->position + parent::position(?)
-make TextureStrategy and AnimatonStrategy a decorator, so we could call something like
	new Animation(new TexturureStrategy(new CacheStrategy(modelFilename),textureFilename))(?)
-glbegin/end is just in cacheStrategy(ok) and RealTimestrategy(ok?)
-make position extend point(?)


