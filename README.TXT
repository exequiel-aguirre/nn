//install environment
>apt-get install build-essential mesa-common-dev libsdl2-dev

To compile:
>g++ src/main.cpp -w   -lGL  -lGLU  -lSDL2


// glut was not used, but in that case it would be...
>apt-get install build-essential mesa-common-dev libsdl2-dev freeglut3-dev
>g++ src/main.cpp -w  -lglut -lGL -lGLU  -lSDL2


BUGS:
-The sphere is not loading the texture(need to add "glTexCoord2f")
-clear header (Adding things that I'm not using...).Check if I can get rid of glu

TODOS:
-surface are performance killers, I think I can fix that by saving the values of getX,getY and getZ,
by adding a CacheDecorator (that extends a Map) and inside has a HashMap, so if the values is not in the hashmap,we calculate,save and return.If it's there, just return.

-try to fix the plane, and make lats/longs variables that can be override by the subclass(24 for a plane makes no sense)

-Add a grassGround using that 0.5*sin(u)*cos(v) and texture
-Add water by using the same as aboce, but u+=0.1, and v+=0.1 (so it moves!)
--if the plane is working fine, maybe we can replace ground. if not make the grass and water passing a map to ground

- for all virtual, I'm using the wrong syntax... is virtual type method_name
-add blending so we can wrap up that lecture