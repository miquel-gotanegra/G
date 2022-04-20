#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord; //entre (0,1)

vec4 black = vec4(0);
vec4 grey = vec4(0.8);

void main()
{	
	//grid 8x8
	
	vec2 texCoord = 8.0 *vtexCoord; //entre(0,8)
	
	int x = int(mod(texCoord.s,2));
	int y = int(mod(texCoord.t,2));
	
	if(x==y) fragColor = grey;
    	else fragColor = black;
    	
}
