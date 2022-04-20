#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vNormal[];
in vec2 vtexCoord[];

out vec4 gfrontColor;
out vec3 gNormal;
out vec2 gtexCoord;

const float speed = 0.5;
uniform float time;
uniform mat4 modelViewProjectionMatrix;

void main( void )
{
	vec3 N = (vNormal[0]+vNormal[1]+vNormal[2])/3;
	
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		
		vec4 P = vec4(speed * time * N,0) + gl_in[i].gl_Position;
		gl_Position = modelViewProjectionMatrix * P;
		EmitVertex();
	}
    EndPrimitive();
}
