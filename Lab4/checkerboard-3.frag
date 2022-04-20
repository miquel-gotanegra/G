#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord; //entre (0,1)

vec4 black = vec4(0);
vec4 grey = vec4(0.8);
uniform float n = 8;
void main()
{	
	//grid 8x8
	
	vec2 texCoord = n *vtexCoord; //entre(0,n)
	
	float x = texCoord.s;
	float y = texCoord.t;
	
	if (fract(x)>0.1 && fract(y)>0.1) fragColor=grey;
  	else fragColor=black;
}
