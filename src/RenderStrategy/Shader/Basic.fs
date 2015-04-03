#version 150

in vec3 vertex0;
in vec2 uv0;
in vec3 normal0;

uniform sampler2D texture,textureDetail;
uniform float mixWeight;
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
	//Phong shading model
	vec3 L = normalize(light.position.xyz - vertex0);
	vec3 E = normalize(-vertex0);
	vec3 R = normalize(-reflect(L,normal0));  

	//Ambient term
	vec4 Iamb = light.ambientProduct;

	//diffuse term
	vec4 Idiff = light.diffuseProduct * max(dot(normal0,L), 0.0);
	Idiff = clamp(Idiff, 0.0, 1.0);     

	// specular term
	vec4 Ispec = light.specularProduct
		* pow(max(dot(R,E),0.0),0.3*light.shininess);
	Ispec = clamp(Ispec, 0.0, 1.0); 

	//apply texture
	fragColor = texture2D(texture, uv0);

	//apply texture detail(if present)
	if(mixWeight > 0.0) fragColor=mix(fragColor,texture2D(textureDetail,mod(uv0*100.0,10)*0.1),mixWeight);

	//if the fragment is transparent, discard it
	if(fragColor.a==0.0) discard;

	//apply the light
	fragColor *=(light.sceneColor + Iamb + Idiff + Ispec);
}