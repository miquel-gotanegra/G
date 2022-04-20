#version 330 core
        
layout(triangles) in; //te llega un triangulo
layout(triangle_strip, max_vertices = 36) out; // sacas un triangle strip de de como maximo 36 vertices

in vec4 vfrontColor[];
in vec3 vNormal[];
in vec2 vtexCoord[];

out vec4 gfrontColor;
out vec3 gNormal;
out vec2 gtexCoord;


uniform mat4 modelViewProjectionMatrix; // para passar de obj->clip
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		
		//multiplicamos por modelViewProjectionMatrix si no lo hemos hecho ya en el VS
		//gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		
		EmitVertex();
	}
    EndPrimitive();
}

/*
 %%%% EJ :CREAR UNA SOMBRA
 
	gfrontColor = vec4(0);
    for( int i = 0 ; i < 3 ; i++ )
	{
		vec4 P = gl_in[i].gl_Position;
		P.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix * P;
		
		EmitVertex();
	}
    EndPrimitive();
    
   %%%% EJ : Dibujar en el viewport con una triangle strip
   
   if(gl_PrimitiveIDIn == 0) // esto es para la eficiencia, para que solo se dibuje una vez
    {
		gfrontColor = vec4(1,0,0,0); // color del vertice cada vez q hagamos emit
		//EL ORDEN ES IMPORTANE!! cada tres vertices consecutivos hacen un triangulo
		gl_Position = vec4(-1,-1,0,1); EmitVertex();
		gl_Position = vec4(1,-1,0,1); EmitVertex();
		gl_Position = vec4(-1,1,0,1); EmitVertex();
		gl_Position = vec4(1,1,0,1); EmitVertex();
	}
		
    EndPrimitive();
    
    RECORDAR MULTIPLICAR SIEMPRE TODOS LOS GL_POSITION POR LA modelViewProjectionMatrix SI NO LO HEMOS HECHO EN EL VS !!!!!!!!!!!!!
    
    vec3 C = (boundingBoxMin+boundingBoxMax)/2;
    float R = distance(boundingBoxMax,boundingBoxMin)/2;
    
    gl_Position = modelViewProjectionMatrix * vec4(C.x - R, y , C.z + R,1); EmitVertex();
    
    
    
    Si hacemos iluminacion por fragmento vamos a tener que passarlos por el GS(sin modificarlos) ej in vNormal out gNormal    

*/
