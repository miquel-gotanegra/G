#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 vEye;
in vec3 N;

uniform vec4 lightAmbient;   // similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;   // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular;  // similar a gl_LightSource[0].specular
uniform vec4 lightPosition;  // similar a gl_LightSource[0].position (sempre estarà en eye space)

uniform vec4 matAmbient;     // similar a gl_FrontMaterial.ambient
uniform vec4 matDiffuse;     // similar a gl_FrontMaterial.diffuse
uniform vec4 matSpecular;    // similar a gl_FrontMaterial.specular
uniform float matShininess;  // similar a gl_FrontMaterial.shininess

void main()
{
    vec3 L = normalize(lightPosition.xyz-vEye);
    
    vec3 R = normalize(2*dot(N,L) * N-L); 
    
    vec3 V = normalize(vec3(0,0,0) - vEye);
    
    float NdL=max(0, dot(N, L));
    float RdV=max(0, dot(R, V));
    float RdVs=0;
    if (NdL>0) RdVs=pow(RdV, matShininess); 
  
    fragColor = matAmbient*lightAmbient + matDiffuse*lightDiffuse*NdL + matSpecular*lightSpecular*RdVs;
}
