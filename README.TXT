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