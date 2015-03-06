#version 120

attribute vec3 vertex;
attribute vec2 uv;
attribute vec2 uvDetail;
attribute vec3 normal;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;

varying vec3 vertex0;
varying vec2 uv0;
varying vec2 uvDetail0;
varying vec3 normal0;

void main()
{
	gl_Position=modelViewProjectionMatrix * vec4(vertex, 1.0);

	//to pass to the fragment shader
	vertex0 = vec3(modelViewMatrix * vec4(vertex,1.0));
	uv0 = uv;	
	uvDetail0 = uvDetail;
	normal0 = normalize(vec3(normalMatrix * vec4(normal,0.0)));

	//this is for the reflection
	gl_ClipVertex=vec4(vertex0,1.0);
}