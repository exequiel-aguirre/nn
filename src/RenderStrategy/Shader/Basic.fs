#version 120

varying vec3 vertex0;
varying vec2 uv0;
varying vec2 uvDetail0;
varying vec3 normal0;

uniform sampler2D texture,textureDetail;
uniform float mixWeight;

void main()
{
	//Phong shading model
	vec3 L = normalize(gl_LightSource[0].position.xyz - vertex0);   
	vec3 E = normalize(-vertex0);
	vec3 R = normalize(-reflect(L,normal0));  

	//Ambient term
	vec4 Iamb = gl_FrontLightProduct[0].ambient;    

	//diffuse term
	vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(normal0,L), 0.0);
	Idiff = clamp(Idiff, 0.0, 1.0);     

	// specular term
	vec4 Ispec = gl_FrontLightProduct[0].specular 
		* pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);
	Ispec = clamp(Ispec, 0.0, 1.0); 

	// the texture affected by all the previous terms
	gl_FragColor = (texture2D(texture, uv0)*(1.0-mixWeight) + texture2D(textureDetail, uvDetail0)*mixWeight )*
		(gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec); 
}