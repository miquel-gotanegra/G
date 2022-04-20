#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D colorMap;
in vec2 vtexCoord;

void main()
{
    vec2 digit;
    
    
    //vtexCoord.s va de [0,1] i queremos partirla en 6, por tanto cada 1/6 ira un nuevo numero
    
    if(vtexCoord.s < 1./6.) digit = vtexCoord*vec2(6./10., 1)+ vec2(0.4,0); //digit 4 
    //nuestro plano esta dividido en 6 (partes de 1/6) i el de los numeros en 10 (partes de 1/10), por tanto para encontrar la correspondecia multiplicamos el punto por 6 y lo dividimos por 10
    																									
    
    else if(vtexCoord.s < 2./6.) digit = vtexCoord * vec2(6./10., 1) // escalem
    							- vec2(1./10,0) //anem al inici
    							+ vec2(0.1,0); // escollim el numero (1)
    
    else if(vtexCoord.s < 3./6.) digit = vtexCoord * vec2(6./10., 1) - vec2(2./10,0) + vec2(0.5,0); //5
    else if(vtexCoord.s < 4./6.) digit = vtexCoord * vec2(6./10., 1) - vec2(3./10,0) + vec2(0.6,0); //6
    else if(vtexCoord.s < 5./6.) digit = vtexCoord * vec2(6./10., 1) - vec2(4./10,0) + vec2(0.6,0); //6
    else digit = vtexCoord * vec2(6./10., 1) - vec2(5./10,0) + vec2(0.4,0); //4
    
    
    vec4 C = texture(colorMap, digit);
    if(C.a < 0.5) discard;
    else fragColor = vec4(0,0,1,0);
}
