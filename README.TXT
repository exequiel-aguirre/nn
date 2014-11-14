//install environment
>apt-get install build-essential mesa-common-dev libsdl2-dev

To compile:
>g++ src/main.cpp -w   -lGL  -lGLU  -lSDL2


// glut was not used, but in that case it would be...
>apt-get install build-essential mesa-common-dev libsdl2-dev freeglut3-dev
>g++ src/main.cpp -w  -lglut -lGL -lGLU  -lSDL2

DEBUG:
>gdb ./a.out
>r
>bt full

PROFILE:
>g++ src/main.cpp -w  -lGL -lGLU  -lSDL2 -pg;./a.out 
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
-all the textures loaded by surfaces seems wrong...

TODOS:
-refactor utils::loadModel to use vertex instead of position. refactor modelObject to use vertex as well.(do this having in mind that at some point we will use glbufferdata from glew.h)
-refactor the cacheStrategy so it uses this modelObject.
-add a getNormals to the surface objects(a vectorial products between first derivatives)
-clear headers (There are things that I'm not using...).Check if I can get rid of glu


-if the plane is working fine, maybe we can replace ground same as we do in water.
-make a modeldecorator that encapsulates all that iterator logic(or maybe a modelobject composite... or something like that).maybe an animation that is a componentdecorator with many component and an it of components insde....or maybe it could be a behavior?


-Big one.(maybe in it's own branch) Render using glBufferData from glew to improve performance
--nice to have:all glbegin/end in one place so the transition to glbuffer data is not so paiful
-make position extend point
-start using glm(?)

-add blending so we can wrap up that lecture