#version 150

in vec3 vertex;
in vec2 uv;
in vec2 uvDetail;
in vec3 normal;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform vec4 reflectPlane;

uniform float time;


void main()
{

	vec3 vertex1=vec3(
		vertex.x+ 0.2*sin(vertex.y*time)*cos(vertex.z*time),
		vertex.y+ 0.2*sin(vertex.z*time)*cos(vertex.x*time),
		vertex.z+ 0.2*sin(vertex.x*time)*cos(vertex.y*time));

	gl_Position=modelViewProjectionMatrix * vec4(vertex1, 1.0);

	//this is for the reflection
	gl_ClipDistance[0]=dot(reflectPlane,modelViewMatrix*vec4(vertex1,1.0));

	gl_PointSize=4.0;
}