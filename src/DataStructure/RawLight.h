#ifndef RawLightH
#define RawLightH

struct RawLight{  
	float position[4];
	float ambientProduct[4];
	float diffuseProduct[4];
	float specularProduct[4];
	float shininess;
	float sceneColor[4];
};

#endif