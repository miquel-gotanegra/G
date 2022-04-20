#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin; //cantonada mínima de la capça englobant
uniform vec3 boundingBoxMax; //cantonada máxima de la capça englobant

vec3 blue = vec3(0,0,1);
vec3 cyan = vec3(0,1,1);
vec3 green = vec3(0,1,0);
vec3 yellow = vec3(1,1,0);
vec3 red = vec3(1,0,0);





void main()
{
    float ymin = boundingBoxMin.y;
    float ymax = boundingBoxMax.y;
    
    float rang = ymax-ymin; // rang de y [0,rang)
    float c = (vertex.y-ymin) / rang; //ens dona un valor entre 0 i 1 
    
    c = c * 4.0; //multipliquem per 4 perque hem de fer 4 interpolacions 		
    				    //diferents (estan en ordre a les definicions)
    vec3 col = vec3(0,0,0);
    
    //mix(baix,dalt,fract) perque com mes gran la part fraccionaria mes endalt i
    // mix = baix(1-frac)+dalt*frac
    if(c == 4) col = blue;
    else if(c>=3) col=mix(cyan,blue,fract(c)); //zona blau-cyan
    else if(c>=2) col=mix(green,cyan,fract(c)); //zona cyan-green
    else if(c>=1) col=mix(yellow,green,fract(c)); //zona green-yellow
    else if(c>0) col=mix(red,yellow,fract(c)); //zona yellow,red
    else col = red;
   
    frontColor = vec4(col,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
