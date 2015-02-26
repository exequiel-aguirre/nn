#version 120

attribute vec3 vertex;
attribute vec2 uv;
attribute vec2 uvDetail;
attribute vec3 normal;

uniform float time;


void main()
{

	vec3 vertex1=vec3(
		vertex.x+ 0.2*sin(vertex.y*time)*cos(vertex.z*time),
		vertex.y+ 0.2*sin(vertex.z*time)*cos(vertex.x*time),
		vertex.z+ 0.2*sin(vertex.x*time)*cos(vertex.y*time));

	gl_Position=gl_ModelViewProjectionMatrix * vec4(vertex1, 1.0);

	//this is for the reflection
	gl_ClipVertex=gl_ModelViewMatrix * vec4(vertex1,1.0);

	gl_PointSize=4.0;
}