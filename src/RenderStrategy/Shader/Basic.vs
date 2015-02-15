#version 120

attribute vec3 vertex;
attribute vec2 uv;
attribute vec3 normal;

varying vec2 uv0;
varying vec3 normal0;

void main()
{
	gl_Position=gl_ModelViewProjectionMatrix * vec4(vertex, 1.0);
	uv0 = uv;	
	normal0 = normal;
}