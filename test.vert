#version 330 core

layout (location = 0) in vec3 vertex; //posicio del vertex, object space
layout (location = 1) in vec3 normal; //normal del vertex, object space, unitaria
layout (location = 2) in vec3 color; //color del vertex, en RGB, entre [0,1]
layout (location = 3) in vec2 texCoord; //coordenadas de textura (s,t)

out vec4 frontColor;
//out vec4 vfrontColor; si usamos GS
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

// x -> rojo, y-> verde, z-> azul

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    
    //posicion del vertice en clipspace
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0); // componente homogenia 1 en 										puntos, 0 en vectores
}
/*

	/assig/grau-g/viewer --> el viewer a la fib
	/assig/grau-g/gedit-config --> activa el highlight de opengl
	Activar snippets a gedit Preferences>Plugins>Snippets per a que
	quan fem def[TAB] ens surtin tots els uniforms
	----------------------------INPUTS----------------------------
				
	OBJECT -> WORLD -> EYE -> CLIP -> NDC -> WINDOW
	
	uniform mat4 modelMatrix; // OBJ -> WORLD
	uniform mat4 viewMatrix; // WORLD -> EYE
	uniform mat4 projectionMatrix; // EYE -> CLIP 
	uniform mat4 modelViewMatrix; // OBJ -> EYE
	uniform mat4 modelViewProjectionMatrix; // OBJ->CLIP == Projection * View * Model
	// CLIP -> NDC : dividim per la component w EN NCD QUEDEN ENTRE [-1,1]
	// NDC -> WIN : glViewport per x,y i glDepthRange per la z
	
	uniform mat4 modelMatrixInverse; // OBJ <- WORLD
	uniform mat4 viewMatrixInverse; // WORLD <- EYE
	uniform mat4 projectionMatrixInverse; // EYE <- CLIP 
	uniform mat4 modelViewMatrixInverse; // OBJ <- EYE
	uniform mat4 modelViewProjectionMatrixInverse; // OBJ <- CLIP
	
	uniform mat3 normalMatrix; //per vectors normals //OBJ->EYE
	
	//luces
	uniform vec4 lightAmbient; //Ia RGB & alpha
	uniform vec4 lightDiffuse; //Id
	uniform vec4 lightSpecular; //Is
	uniform vec4 lightPosition; //en eye space
	
	//materiales
	uniform vec4 matAmbient; //Ka
	uniform vec4 matDiffuse; //Kd
	uniform vec4 matSpecular; //Ks
	uniform float matShininess; //Exponente
	
	uniform vec3 boundingBoxMin; //cantonada de la capça englobant
	uniform vec3 boundingBoxMax; //cantonada de la capça englobant
	
	uniform vec2 mousePosition; //pos del cursor (widows space);origen BL
	
	uniform float time;
	
	----------------------------OUTPUTS----------------------------
	
	out vec4 gl_Position //clipspace
	
	qualsevol altre que volguem passar al fragment shader
	
	----------------------------FUNCIONS----------------------------
	mat3 m = mat3(vec3(1,0,1),vec3(1,1,0),vec3(1,0,0)) on cada vec3 es una COLUMNA de la matriu
	[1 1 1]
	[0 1 0]
	[1 0 0]
	
	fract(x) retorna la part fraccionaria [0,1)
	
	mod(x,y) retorna la x mod y entre [0,y)
	
	mix(a,b,t) si t=0 retorna a, si t=1 retorna b, sino retorna una interpolacio entre a i b :
	 a(1-t) + bt
	NO USAR CON VECTORES (con colores si)!! USAR  V’ = (1.0-w)V + wF
	
	sin(x) // en radianes 
	-> Sinusoïdals A * sin(2pi * freq * t + fase_ini) 
	--> A es hasta donde llega el recorrido por defecto [0,1]
	
	#define M_PI 3.14159265358979323846
	const float PI=acos(-1);
	
	dot(N,L) --> producto escalar entre dos vecotres, aka N·L
	cross(N,L) -->producto vectorial, aka ||N x L||
	
	lenght(cross(N,L)) --> modulo del producto vectorial (area del paralelogramo)
	
	
	pow(X,Y) --> potencia, aka X^Y
	
	length(A-B) --> longitud del vector AB, A i B punts
	distance(A,B) --> distancia entre els punts A i B
	
	translate(tx,ty,tz) * vec4(x,y,z,1)
	
	translate(tx,ty,tz)=	[1 0 0 tx] // igual a sumar x+tx,y+ty,z+tz
							[0 1 0 ty]
							[0 0 1 tz]
							[0 0 0 1 ]

	scale(Sx,Sy,Sz)=	[Sx 0 0 1] // igual a  Sx*x,Sy*y,Sz*tz
						[0 Sy 0 1]
						[0 0 Sz 1]
						[0 0 0  1]
	
	
	mat3 m = mat3(vec3(1,0,0),vec3(0,cos(a),sin(a)),vec3(0,-sin(a),cos(a)));
	glRoate*(a,1,0,0)= 	[1   0       0    0] 
						[0 cos(a) -sin(a) 0]
						[0 sin(a)  cos(a) 0]
						[0   0       0    1]
	 
	
	mat3 m = mat3(vec3(cos(a),0,-sin(a)),vec3(0,1,0),vec3(sin(a),0,cos(a)));
	glRoate*(a,0,1,0)= 	[cos(a)  0 sin(a) 0] 
						[  0     1   0    0]
						[-sin(a) 0 cos(a) 0]
						[  0     0    0   1]
	
	
	mat3 m = mat3(vec3(cos(a),sin(a),0),vec3(-sin(a),cos(a),0),vec3(0,0,1));
	glRoate*(a,0,0,1)= 	[cos(a) -sin(a) 0  0] 
						[sin(a)  cos(a) 0  0]
						[  0       0    1  1]
						[  0       0    0  1]
	
	divisio de perspectiva gl_Position.xyz/gl_Position.w 
	//(gl_Position.y /gl_Position.z) esta entre [-1,1], si sumem +1 ens queda entre [0,2]
				
	----------------------------ILUMINACIÓN----------------------------
	 Puede ser en VS o FS --> Si la iluminacion es por fragmento, el VS le tiene que pasar al FS
	 con outs la posicion del punto i la normal (en eye space)
	 
	 vec4 lightPosition x,y,z,w -> w=1 luz posicional, w=0 luz direccional
	 
	 %%%%%%%%--LA ILUMINACION TODA EN EYE SPACE!!--%%%%%%%%%%
	 
	 vertex V i normal N estan en OBJ space (hay que pasarlos a EYE) V con modelView i N con normalMatrix 
	 lightPosition ya esta en EYE space.
	 observador en eye space (0,0,0,1)
	 
	 si multiplicamos una matriz y un vector(normalMatrix * normal) o lo interpolamos linealmente
	 (ex. out vec3 N) se pierde la normalidad del vector
	 antes de hacer calculos con vectores hay que normalizaros--> normalize(vec) 
	 ya que dot(V,U) asume que los vectores son unitarios
	  
	 usamos:	
	 -la normal del vertice UNITARIO N
	 -el vector de iluminación L = normalize(lightPosition.xyz-vEye);
	 - angulo entre N i L --> N·L = cos(ALPHAi) //reflexion difusa
	 - reflexion de L respecto a la normal,el vector R, R=2(N·L)N-L
	 - el vector del vertice hasta el observador OBS, el vector UNITARIO V = normalize(vec3(0,0,0) - vEye);
	 - angulo entre R i V --> R·V = cos(BETA) //reflexion especular
	 	
	 
	 %%%%%%%%%%%%%%%%% MODELO DE PHONG %%%%%%%%%%%%%%%%%
	 
	 frontColor = Ke    +  Ka(Ma+Ia) + KdId(N·L) + KsIs(R·V)^shininess
	            ignorar    ambiente     difusa        especular
	 
	 donde K = reflectividad material , I = color iluminacion y shininess que se obtiene con uniform float matShininess
	 los materiales K se obtienen con los uniforms vec4 matAmbient matDiffuse matSpecular
	 las luces I se obtienen con los uniforms vec4 lightAmbient lightDiffuse lightSpecular
	 Ma no se usa. 
	 
	 OJO!! -> si  N·L < 0 aporta luz negativa, asi que hay que hacer max(0,N·L) i IGNORAR LA LUZ ESPECULAR
	 
	 OJO!! --> si R·V < 0 aporta luz negativa,asi que hay que hacer max(0,R·L);
	 
	 si L es constante, la luz esta infinitamente alejada en la direccion de L
	 
	vec4 light(vec3 N, vec3 V, vec3 L)
	{  
		N=normalize(N); V=normalize(V); L=normalize(L);
		vec3 R = normalize( 2.0*dot(N,L)*N-L );  
		float NdotL = max( 0.0, dot( N,L ) );  
		float RdotV = max( 0.0, dot( R,V ) );  
		float Idiff = NdotL;  float Ispec = 0;
		if (NdotL>0) Ispec=pow( RdotV, matShininess );
		return  matAmbient  * lightAmbient + 
	   			matDiffuse  * lightDiffuse * Idiff+ 
	      		matSpecular * lightSpecular * Ispec;
	}

    			
*/ 
