#version 330 core

in vec4 frontColor;
out vec4 fragColor;
uniform sampler2D colormap;
in vec2 vtexCoord;
in vec3 N;
void main()
{
    fragColor = texture(colormap,vtexCoord);
    
    
    vec2 C1 = vec2(0.34,0.65) -0.1*N.xy;
    vec2 C2 = vec2(0.66,0.65) -0.1*N.xy;
    
	float d1 = distance(C1,vtexCoord);
	float d2 = distance(C2,vtexCoord);
	
	float dentro1 =step(0.05,d1);
	float dentro2 =step(0.05,d2);
	
	if(dentro1==0 || dentro2==0) fragColor = vec4(0);
	else fragColor = texture(colormap,vtexCoord);
    
}
