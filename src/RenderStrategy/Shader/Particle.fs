#version 120

varying vec3 vertex0;
varying vec2 uv0;
varying vec2 uvDetail0;

uniform sampler2D texture,textureDetail;
uniform float mixWeight;

void main()
{
	//apply texture and texture detail
	gl_FragColor = mix(texture2D(texture, uv0),texture2D(textureDetail, uvDetail0),mixWeight);
}