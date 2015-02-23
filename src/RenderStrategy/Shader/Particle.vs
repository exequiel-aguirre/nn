#version 120

attribute vec3 vertex;
attribute vec2 uv;
attribute vec2 uvDetail;
attribute vec3 normal;

uniform float time;

varying vec3 vertex0;
varying vec2 uv0;
varying vec2 uvDetail0;
varying vec3 normal0;

void main()
{

	vec3 vertex1=vec3(
		vertex.x+ 0.2*sin(vertex.y*time)*cos(vertex.z*time),
		vertex.y+ 0.2*sin(vertex.z*time)*cos(vertex.x*time),
		vertex.z+ 0.2*sin(vertex.x*time)*cos(vertex.y*time));

	gl_Position=gl_ModelViewProjectionMatrix * vec4(vertex1, 1.0);

	//to pass to the fragment shader
	vertex0 = vec3(gl_ModelViewMatrix * vec4(vertex1,1.0));
	uv0 = uv;	
	uvDetail0 = uvDetail;
   	normal0 = normalize(gl_NormalMatrix * normal);

	//this is for the reflection
	gl_ClipVertex=vec4(vertex0,1.0);
	gl_PointSize=5.0;
}