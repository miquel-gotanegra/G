#version 330 core

vec4 gl_FragCoord;
bool gl_FrontFacing;


in vec4 frontColor; 
out vec4 fragColor;
in vec2 vtexCoord; //(s,t), ambas entre 0 i 1

void main()
{
	
	fragColor = frontColor;
    //discard; per descartar un fragment
    //gl_FragCoord --> coodenades del centre del fragment en NCD entre [-1,1]
}

/*
es fa servir per calcular el color si el vertex shader no ha calculat la iluminacio
----------------------------INPUTS----------------------------
vec4 gl_FragCoord; //window space x,y-> 0 <= x =< width, 0 <= y =< height , 0 <= z <= 1 , 1/w = -1/zeye
bool gl_FrontFacing; // el fragment l'ha generat una primitiva frontface?

//OUTS DEL VSHADER
vec4 frontColor;

----------------------------OUTPUTS----------------------------
float gl_FragDepth; // z en window space [0,1]
vec4 fragColor //RGB & alpha

----------------------------TEXTURAS----------------------------
uniform sampler2D colorMap; --> la textura 0
uniform sampler2D colorMap1 2 o 3;

in vec2 vtexCoord; --> coordenadas de textura (s,t) recibidas del VS

fragColor = texture(colorMap, vtexCoord); // nomes la textura
fragColor = frontColor * texture(colorMap,vtexCoord); // amb iluminacio al VS

si hacemos 5*vtexCoord -> la textura aparecera repetida 5 veces mas
si hacemos 0.5*vtexCoord --> la mitad de veces q la original
si hacemos -1*vtexCoord --> invertimos la textura 
vtexCoord = texCoord + vec2(2,5) no hace nada ya que la las coordenadas s,t de textura son entre 0 i 1 (parte fraccionaria) i por tanto los numeros enteros no desplazan la textura (WRAPING MODE) 

mirar coordenadas s,t --> if(vtexCoord<0) fragColor =  vec4(0); // black
fragColor = vec4(vtexCoord,0,0) --> rojo s, verde t

interpolar texturas (cambiar negro por otra textura)--> if (length(c.rgb) > 1) //length es la distancia del vector

----------------------------ANIMACION----------------------------

uniform float time;
uniform float slice=1.0/30.0; //temps per frame, equival a 30FPS

int frame = int( mod( (time/slice) ,TotalFrames) ); // el frame para un tiempo concreto

int x = frame % numCols;
int y = (numFilas-1) - frame/numCols; // cada numCols frames cambiem de linia, i el primer frame esta en a dalt a la esquerra

vec2 texCoord= vtexCoord*vec2(1.0/numCols, 1.0/numFilas) //escalamos la textura
			+ vec2(x/numCols,y/numFilas);        //sumamos x y del frame que queramos dividido por el escalado para que esté entre 0 y 1
			
fragColor=texture(explosion, texCoord);
  	fragColor*=fragColor.w;
  	
----------------------------TEXTURAS PROCEDURALES----------------------------

Ej circulo gradiente

in vec3 P ;// vertex en OBJ space
vec4 red = vec4(1,0,0,0);
vec4 yellow = vec4(1,1,0,0);

main() 
	vec2 C = vec2(0,0); //centro del modelo en OBJ space (plane) vertices entre [-1,-1] i [1,1]
	float d = distance(C,P.xy);
	
	fragColor = mix(red,yellow,d/sqrt(2)); dividimos entre la distancia maxima possible para que nos quede entre 0 i 1
	
Funciones dFdx() y dFdy(): derivadas parciales, aka la diferencia entre el valor en este fragmento y en uno vecino.
se puedesn usar con dFdx(vtexCoord.s),dFdx(color),dFdx(P),..

funciones: 
	-step(edge,x) nos retorna 0 si x es menor que x, si es mayor devuelve 1
	Ej. pintar una esfera negra i el resto blanco 
		calculamos distancia d del centro de la esfera al punto
		vec4(step(R,d))
		
	-smoothstep(edge0,edge1,x) x menor que edge 0 devuelve 0, entre edge0 i edge1 valor entre 0 i 1 y si es mayor a edge1 1
	Ej. smoothstep(edge-filtro,edge+filtro,d) --> filtro = 0.7 *lenght( vec2(dFdx(d),dFdy(d)) ); // lo q varia d en un pixel

La part de l’espai de textura entre el (0,0) i el (1,1) -> para hacer grids multiplicamos la posicion de textura por 8 (8x8)

*/
