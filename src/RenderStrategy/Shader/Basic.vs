#version 150

in vec3 vertex;
in vec2 uv;
in vec2 uvDetail;
in vec3 normal;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;
uniform vec4 reflectPlane;

out vec3 vertex0;
out vec2 uv0;
out vec2 uvDetail0;
out vec3 normal0;

void main()
{
	gl_Position=modelViewProjectionMatrix * vec4(vertex, 1.0);

	//to pass to the fragment shader
	vertex0 = vec3(modelViewMatrix * vec4(vertex,1.0));
	uv0 = uv;	
	uvDetail0 = uvDetail;
	normal0 = normalize(vec3(normalMatrix * vec4(normal,0.0)));

	//this is for the reflection
	gl_ClipDistance[0]=dot(reflectPlane,vec4(vertex0,1.0));
}