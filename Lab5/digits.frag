#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D colorMap;
uniform float time;


void main()
{
	//vtexCoord.s va del 0 al 3 pel VS
	
	vec2 digit;
	
	if(vtexCoord.s < 1) digit = vtexCoord * vec2(1./10.,1) + vec2(  (((int(time)%1000) /100) *0.1 ),0);
	
	else if(vtexCoord.s < 2)digit = vtexCoord * vec2(1./10.,1) - vec2(0.1,0) + vec2(  (((int(time)%100) /10) *0.1 ),0);
	else digit = vtexCoord * vec2(1./10.,1) -vec2(0.2,0)  + vec2(  ((int(time)%10)*0.1 ),0);
	
	vec4 C = texture(colorMap,digit);
	
	if(C.a < 0.5) discard;
	
    fragColor = vec4(1,0,0,0);
}
