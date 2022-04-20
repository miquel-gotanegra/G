#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;


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
    vec3 N = normalize(normalMatrix * normal);
    
    vec3 vEye = (modelViewMatrix * vec4(vertex,1.0)).xyz;
    
    vec3 L = normalize(lightPosition.xyz-vEye);
    
    vec3 R = normalize(2*dot(N,L) * N-L); 
    
    vec3 V = normalize(vec3(0,0,0) - vEye);
    
    float aux=0;
    if(max(0, dot(N, L)) > 0) aux=1;
    frontColor = matAmbient*lightAmbient + 
    		matDiffuse*lightDiffuse*max(0, dot(N, L)) +
    		matSpecular*lightSpecular*pow( max(0, dot(R, V) ),matShininess)*aux;
    		
    vtexCoord = texCoord;
    
    //posicion del vertice en clipspace
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0); // componente homogenia 1 en 										puntos, 0 en vectores
}
