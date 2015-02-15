#version 120

attribute vec3 vertex;
attribute vec2 uv;
attribute vec3 normal;

varying vec3 vertex0;
varying vec2 uv0;
varying vec3 normal0;

void main()
{
	gl_Position=gl_ModelViewProjectionMatrix * vec4(vertex, 1.0);

	vertex0 = vec3(gl_ModelViewMatrix * vec4(vertex,1.0));
	uv0 = uv;	
   	normal0 = normalize(gl_NormalMatrix * normal);
}