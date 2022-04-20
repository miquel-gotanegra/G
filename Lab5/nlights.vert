#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

out vec3 N;
out vec3 L;
out vec3 V;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;

void main()
{
   vec3 vEye = (modelViewMatrix*vec4(vertex,1.0)).xyz;
	N = normalize(normalMatrix * normal);
 	L = normalize(vec3(10,0,0)-vEye);
 	V = normalize(vec3(0,0,0) - vEye);

    
    
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
