#version 150

in vec3 vertex0;
in vec2 uv0;
in vec3 normal0;
in vec4 depthMapProjVertex0;
in mat3 frenetMatrix0;

uniform sampler2D texture,textureDetail,textureNormal;
uniform vec3 texturesActive;
uniform sampler2DShadow depthMap;
uniform float time;
uniform struct Light{
	vec4 position;
	vec4 ambientProduct;
	vec4 diffuseProduct;
	vec4 specularProduct;
	float shininess;
	vec4 sceneColor;
} light;

out vec4 fragColor;

void main()
{
	//apply texture
	fragColor = texture2D(texture, uv0*texturesActive.x);
	//if the fragment is transparent, discard it
	if(fragColor.a==0.0) discard;

	//apply texture detail(if present)
	if(texturesActive.y > 0.0) fragColor=mix(fragColor,texture2D(textureDetail,uv0*texturesActive.y),0.5);

	//bump
	vec3 N=normal0;
	if(texturesActive.z>0.0) N = frenetMatrix0*((2*(texture2D(textureNormal, uv0*texturesActive.z + time*0.01).xyz))-1.0);

	//Phong shading model
	vec3 L = normalize(light.position.xyz - vertex0);
	vec3 E = normalize(-vertex0);
	vec3 R = normalize(-reflect(L,N));
	//Ambient term
	vec4 Iamb = light.ambientProduct;
	//diffuse term
	vec4 Idiff = clamp(light.diffuseProduct*max(dot(N,L), 0.0),0.0,1.0);
	// specular term
	vec4 Ispec = clamp(light.specularProduct*pow(max(dot(R,E),0.0),0.3*light.shininess),0.0,1.0);

	//shadow
	float shadow=clamp(textureProj(depthMap,depthMapProjVertex0) + 0.3,0.0,1.0);
	fragColor*=shadow;

	//apply the light
	fragColor *=(light.sceneColor + Iamb + Idiff + Ispec);
}