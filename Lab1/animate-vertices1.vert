#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;


uniform float amplitude = 0.1; 
uniform float freq = 1; // expressada en Hz
uniform float time;
float M_PI = 3.14159265358979323846;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    vec3 NewPos = vertex + normal * (amplitude * sin(2*M_PI * freq * time));
    //A * sin(2pi * freq * t + fase_ini)
    frontColor = vec4(1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(NewPos,1.0);
}
