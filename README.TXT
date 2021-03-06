//install environment
>apt-get install build-essential mesa-common-dev libsdl2-dev libglew-dev

To compile:
>g++ src/main.cpp -Wall -std=c++11  -lGL  -lSDL2 -lGLEW



DEBUG:
>gdb ./a.out
>r
>bt full

PROFILE:
>g++ src/main.cpp  -Wall -std=c++11  -lGL  -lSDL2 -lGLEW -pg;./a.out
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

BLENDER TEXTURE:
-Bake
--Select the suit and change to "Edit Mode".
--Select "UV Editing" screen and select the Suit image
--now if you select "Texture Paint" mode, it should show with the suit
--create a new image

--go back to default view,add a sun lamp, and select the camera icon,disable all but texture in the Shading option and  click bake option (last on the right bar).
-Re order the uv.
--Choose the body and go to UV edit screen and then choose edit mode.
--There de-activate "uv-mesh sync"(cube with and arrow on the bottom bar in the uv editor).So now you can select "UV selection mode" to island.
--Once something is selected you can Rotate (R),Translate(G),Scale(S). Arrange the body parts to unused texture
--Now select "Texture Paint Mode" and paint it.
BUMP MAPPING:
>sudo apt-get install gimp-normalmap
-Open an image with Gimp, and go to Filters>Map>NormalMap...

MAKEHUMAN:
-For making it save an skin texture, select one different than the default

QTCREATOR:
-To be able to step into a third party lib, you need to add the library path to the includes.For example, add /usr/include/bullet to example.includes .

QAPITRACE:
>apitrace trace  ./a.out 
>qapitrace
-Select profile
BUGS:
-The small ball is passing through the big one.This is most likely related to sleeping.
-In the reduced polygon we are not effectively removing duplicated points.(See the box for example)
-The fog is not working.(some code need to be added to the shader, more info at the bottom)



TODOS:
-Right now we are using Animation and Skeleton as if they were the same thing.
-We should not put the contact points in the collision status, but in the manifold, since it's one set of point's per pair, not per object.(now we are distributiong the 4 points among the pair of collisions, for example 2 points for floor-box1 and 2 points for floor-box2)
-Unify the whole manifold,collsionStatus,ContactPoint into one
-Matrix: remove vector
-To get all collision points maybe we can check the distance of all points to the plane formed by the impact normal and impact point.
-DELTA_TIME should be an global constant

-implement a factory so we can avoid thius chaotics constructors
-try template for ciclyc reference.

Notes:
-Weird bug,
	Program received signal SIGSEGV, Segmentation fault.
	0x0804a86e in ListenerManager::callMouseListeners (this=0x81fabe0, button=...) at src/Server/../Application/../Listener/ListenerManager.h:33
	33              (*it)->onMouseButtonDown(button);

	This just happens if the the ball's motionBehavior was the 17's element in the vector.
	The solution was to reserve more places in the vector on the constructor.
	Most likely, this happens when the vector needs to resize.

-To add fog add this at end of the fragment shader(the effect is not so well achieved)
float z=gl_FragCoord.z / gl_FragCoord.w;
	if(z>gl_Fog.start){
		//float fog = clamp((gl_Fog.end-gl_FogFragCoord)*gl_Fog.scale,0.0,1.0);
		const float LOG2E = 1.442695; // = 1 / log(2)
		float fog = exp2(-gl_Fog.density * gl_FogFragCoord * LOG2E);	
		gl_FragColor=mix(gl_FragColor,gl_Fog.color,fog);
	}

-When 2 objects with std::numeric_limits<float>::max() collide, everything goes to hell (for example, most things just dissapear)
-Warning:the std::max_element enters in an infinite loop if p*v is nan



Idea
-Maybe the dancing box is because when using the cached point, I apply the impulse with the NEW normal instead of the contact's point normal