#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 N;
in vec3 V;
in vec3 L;

uniform vec4 lightAmbient;   // similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;   // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular;  // similar a gl_LightSource[0].specular
uniform vec4 lightPosition;  // similar a gl_LightSource[0].position (sempre estarà en eye space)

uniform vec4 matAmbient;     // similar a gl_FrontMaterial.ambient
uniform vec4 matDiffuse;     // similar a gl_FrontMaterial.diffuse
uniform vec4 matSpecular;    // similar a gl_FrontMaterial.specular
uniform float matShininess;  // similar a gl_FrontMaterial.shininess

uniform  int n=2;

const float pi = 3.141519;

vec4 light(vec3 N, vec3 V, vec3 L)
	{  
		N=normalize(N); V=normalize(V); L=normalize(L);
		vec3 R = normalize( 2.0*dot(N,L)*N-L );  
		float NdotL = max( 0.0, dot( N,L ) );  
		float RdotV = max( 0.0, dot( R,V ) );  
		float Idiff = NdotL;  float Ispec = 0;
		if (NdotL>0) Ispec=pow( RdotV, matShininess );
		return  //matAmbient  * lightAmbient + 
	   			(matDiffuse  * lightDiffuse * Idiff )/ sqrt(n)+ 
	      		matSpecular * lightSpecular * Ispec;
	}

void main()
{
  	//una circumferecia te 2pi rads, per calcular on estaran la resta de llums dividim 2pi/n
  	
  	float angle = (2*pi)/n;
  	vec3 newL;
  	vec4 color = vec4(0);
  	float a=0;
  	for(int i=0;i<n;++i){
  		newL = mat3(vec3(cos(a),sin(a),0),vec3(-sin(a),cos(a),0),vec3(0,0,1)) * L;
  		color += light(N,V,newL);
  		a += angle;
  	 }
    fragColor = color;
}
