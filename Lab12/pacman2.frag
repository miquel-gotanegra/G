#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D colorMap;
in vec2 vtexCoord;
uniform float size = 10;

void main()
{
	//vec2 mono = vec2(vtexCoord.s/6,vtexCoord.t)*size; //primero escala a 1/6 para que solo salga uno i luego reescala a size para que cada imagen sea del tamaño que toca
	vec2 mono=vtexCoord;
   // amb iluminacio al VS
     //fragColor = texture(colorMap,-1*mono + vec2(1./6.,0)); 
     //return;
    float s = vtexCoord.s*size; //s y t de 0 a size
    float t = vtexCoord.t*size;
    
    float fs = fract(s);
    float ft = fract(t);
    
   
    									
    if((floor(s)==0 || floor(s)==(size-1)) && ( floor(t)==(size-1) || floor(t)==0)){ //esquinas
    
    	if(floor(s)==0 && floor(t)==0) {
    	 mono =-1 *  vtexCoord * vec2(size/6., size) // escalem
    							- vec2(floor(s)/6.,0) //anem al inici
    							+ vec2(5./6.,0); // escollim el numero (1)
    	}
    	
    	else if(floor(s)==size-1 && floor(t)==0) {
    	 mono =vec2(1,-1)*  vtexCoord * vec2(size/6., size) // escalem
    							- vec2(floor(s)/6.,0) //anem al inici
    							+ vec2(4./6.,0); // escollim el numero (1)
    	}
    	else if(floor(s)==0 && floor(t)==size-1) {
    	 mono = vec2(-1,1) * vtexCoord * vec2(size/6., size) // escalem
    							- vec2(floor(s)/6.,0) //anem al inici
    							+ vec2(5./6.,0); // escollim el numero (1)
    	}
    	
    	else mono =vtexCoord * vec2(size/6., size) // escalem
    							- vec2(floor(s)/6.,0) //anem al inici
    							+ vec2(4./6.,0); // escollim el numero (1)
    	fragColor = texture(colorMap,mono); 
    							
     }
     
     
     else if ((floor(s)<1 || floor(s)>(size-2)) || ( floor(t)>(size-2) || floor(t)<1)){
     	
     	if(floor(t)!=size-1 && floor(t)!=0)
    		mono =  vec2(mono.t,mono.s) * vec2(size/6., size) // escalem
    							 - vec2(floor(t)/6.,0) //anem al inici
    							+ vec2(3./6.,0); // escollim el numero (1)
    							
    	else mono =  mono * vec2(size/6., size) // escalem
    							 - vec2(floor(s)/6.,0) //anem al inici
    							+ vec2(3./6.,0); // escollim el numero (1)
    	fragColor = texture(colorMap,mono); 
     }
     
     else {
     mono = vtexCoord * vec2(size/6., size) // escalem
    							- vec2(floor(s)/6.,0) //anem al inici
    							+ vec2(5./6.,0); // escollim el numero (1)
    	fragColor = texture(colorMap,mono); }
     
    
}
