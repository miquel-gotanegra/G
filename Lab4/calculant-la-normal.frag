#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec3 vEye;

in vec3 V;

//luces
	uniform vec4 lightAmbient; //Ia RGB & alpha
	uniform vec4 lightDiffuse; //Id
	uniform vec4 lightSpecular; //Is
	uniform vec4 lightPosition; //en eye space
	
	//materiales
	uniform vec4 matAmbient; //Ka
	uniform vec4 matDiffuse; //Kd
	uniform vec4 matSpecular; //Ks
	uniform float matShininess; //Exponente




void main()
{

	vec3 L = normalize(lightPosition.xyz-vEye);
	vec3 N=normalize(cross(dFdx(V), dFdy(V)));
    	fragColor = frontColor*N.z;
}
