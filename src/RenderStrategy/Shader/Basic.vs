#version 150

in vec3 vertex;
in vec2 uv;
in vec3 normal;
in vec3 tangent;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;
uniform vec4 reflectPlane;

out vec3 vertex0;
out vec2 uv0;
out vec3 normal0;
out mat3 frenetMatrix0;

void main()
{
	gl_Position=modelViewProjectionMatrix * vec4(vertex, 1.0);

	//to pass to the fragment shader
	vertex0 = vec3(modelViewMatrix * vec4(vertex,1.0));
	uv0 = uv;
	normal0 = normalize(vec3(normalMatrix * vec4(normal,0.0)));
	vec3 tangent0 = normalize(vec3(normalMatrix * vec4(tangent,0.0)));
	tangent0 = normalize(tangent0 - dot(tangent0,normal0)*normal0);
	vec3 binormal0 = cross(tangent0,normal0);
	frenetMatrix0=mat3(tangent0,binormal0,normal0);

	//this is for the reflection
	gl_ClipDistance[0]=dot(reflectPlane,vec4(vertex0,1.0));
}