//install environment
apt-get install build-essential mesa-common-dev freeglut3-dev libsdl2-dev

To compile:
>g++ src/main.cpp -w   -lGL  -lGLU  -lSDL2

// also with 
>g++ src/main.cpp -w  -lglut -lGL -lGLU  -lSDL2
