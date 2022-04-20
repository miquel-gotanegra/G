#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

vec4 red = vec4(1,0,0,1);
vec4 white = vec4(1);

void main()
{
	vec2 C = vec2(0.5,0.5);
	float d = distance(C,vtexCoord);
	
	float dentro = step(0.2,d);
	
	if(dentro==0) fragColor = red;
	else fragColor=white;
	
	//float filtro = 0.7 *length( vec2(dFdx(d),dFdy(d)) );
	//float w = smoothstep(0.2-filtro,0.2+filtro,d); 
	
	//fragColor = mix(red,white,w);
}
