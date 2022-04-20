#version 330 core
out vec4 fragColor;

uniform sampler2D colorMap;

uniform float SIZE;

const int W = 4; // filter size: 2W*2W

void main()
{
    vec2 st = (gl_FragCoord.xy) / SIZE;
    float a = 4.0/SIZE;
	
	fragColor = texture2D(colorMap,st);
	if(length(fragColor.rgb)==0) { //
		float count = 0.0;
		for (int i=-W; i<W; ++i)
		for (int j=-W; j<W; ++j)
		{
		    vec4 tmp = texture(colorMap, st+vec2(a*float(i), a*float(j)));
		    if (length(tmp.rgb)>0.0) // assumes background is black 
		    {
		        count++;
		    } 
		}
		count /= (2*W+1)*(2*W+1);
		    
		fragColor = vec4(2*count);
    }
}

