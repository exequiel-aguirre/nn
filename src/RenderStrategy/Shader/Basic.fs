#version 150

in vec3 vertex0;
in vec2 uv0;
in vec3 normal0;

uniform sampler2D texture,textureDetail,textureNormal;
uniform vec3 texturesActive;
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
	if(texturesActive.z>0.0){
		N = texture2D(textureNormal, uv0*texturesActive.z + time*0.01).xyz;
		N = N * 2.0 - 1.0;
	}

	//Phong shading model
	vec3 L = normalize(light.position.xyz - vertex0);
	vec3 E = normalize(-vertex0);
	vec3 R = normalize(-reflect(L,N));

	//Ambient term
	vec4 Iamb = light.ambientProduct;

	//diffuse term
	vec4 Idiff = light.diffuseProduct * max(dot(N,L), 0.0);
	Idiff = clamp(Idiff, 0.0, 1.0);     

	// specular term
	vec4 Ispec = light.specularProduct
		* pow(max(dot(R,E),0.0),0.3*light.shininess);
	Ispec = clamp(Ispec, 0.0, 1.0); 


	//apply the light
	fragColor *=(light.sceneColor + Iamb + Idiff + Ispec);
}