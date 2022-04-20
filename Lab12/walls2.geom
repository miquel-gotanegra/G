#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
uniform vec3 boundingBoxMin; // esta en OBJ 
uniform vec3 boundingBoxMax; // esta en OBJ 
uniform mat4 modelViewProjectionMatrix; //OBJ->CLIP
uniform mat4 viewMatrixInverse; // WORLD <- EYE


void main( void )
{
	vec4 cam = vec4(0,0,0,1); //camera en eye
	vec4 pos_cam =viewMatrixInverse * cam;
	
	float mx = boundingBoxMin.x;
	float my = boundingBoxMin.y;
	float mz = boundingBoxMin.z;
	float Mx = boundingBoxMax.x;
	float My = boundingBoxMax.y;
	float Mz = boundingBoxMax.z;
	
	bool inside = false;
	if(pos_cam.x > mx && pos_cam.x < Mx && pos_cam.y > my && pos_cam.y < My && pos_cam.z > mz && pos_cam.z < Mz) inside = true;
	for( int i = 0 ; i < 3 ; i++ )
	{
		if(inside) gfrontColor = 2 * vfrontColor[i];
		else gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    
    if(gl_PrimitiveIDIn == 0) {
		gfrontColor = vec4(0,1,1,0);
		
		//inferior
		gfrontColor = vec4(0,1,0,1);
		gl_Position = modelViewProjectionMatrix * vec4(mx,my,mz,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(mx,my,Mz,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(Mx,my,mz,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(Mx,my,Mz,1); EmitVertex();
		EndPrimitive();
		
		//dreta
		gfrontColor = vec4(1,0,0,1);
		gl_Position = modelViewProjectionMatrix * vec4(Mx,my,Mz,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(Mx,my,mz,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(Mx,My,Mz,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(Mx,My,mz,1); EmitVertex();
		EndPrimitive();
		
		//esquerra 
		gfrontColor = vec4(1,0,0,1);
		gl_Position = modelViewProjectionMatrix * vec4(mx,my,Mz,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(mx,my,mz,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(mx,My,Mz,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(mx,My,mz,1); EmitVertex();
		EndPrimitive();
		
		//derrere
		gfrontColor = vec4(0,0,1,1);
		gl_Position = modelViewProjectionMatrix * vec4(mx,my,mz,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(Mx,my,mz,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(mx,My,mz,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(Mx,My,mz,1); EmitVertex();
		EndPrimitive();
    }
}
