#version 120

varying vec2 uv0;
varying vec3 normal0;

uniform sampler2D sampler;

void main()
{
	//gl_FragColor=vec4(1.0,0.0,0.0,1.0);
	gl_FragColor = texture2D(sampler, uv0)*
		clamp(dot(vec3(-0.5,0.5,0.5), normal0), 0.0, 1.0);
}