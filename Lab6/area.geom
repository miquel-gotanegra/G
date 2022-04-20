#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 projectionMatrix;
const float areamax = 0.0005;

void main( void )
{

	vec3 U = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 V = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	
	float area = length(cross(U,V))/(2*areamax);
	
	gfrontColor = mix(vec4(1,0,0,1),vec4(1,1,0,1),area);
	for( int i = 0 ; i < 3 ; i++ )
	{
		
		gl_Position = projectionMatrix*gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}
