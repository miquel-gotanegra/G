#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 NvectorEYE;
in vec4 vertexEYE;

void main()
{
    fragColor = frontColor*NvectorEYE.z;
}
