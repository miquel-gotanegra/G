#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

vec4 white = vec4(1);
vec4 green = vec4(0,0.8,0,0);


void main()
{
	vec2 texCoord = vec2(4.0,3.0)*vtexCoord;
	
	vec2 C1 = vec2(1.4,1.5);
	vec2 C2 = vec2(2.,1.5);
	
	
	float d = distance(C1,texCoord);
	
	float dentro1 =step(1.1,d); //circulo blanco
	
	float dentro2 = (step (1.1,distance(C2,texCoord))); //ciruclo verde
	
	float dentro3=1;
	
	float x = texCoord.s;
	float y = texCoord.t;
	
	if( x > 2.5 && x < 3.5 && y > 1 && y < 2) dentro3=0;
	
	
	if( (dentro1==0 && !(dentro2==0)) || dentro3==0) fragColor = white;
	else fragColor=green;
}
