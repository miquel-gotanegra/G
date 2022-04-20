#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;


uniform sampler2D explosion;
uniform sampler2D frameMap1;
uniform float time;
uniform float slice=1.0/30.0; //temps per frame, equival a 30FPS

//mod(frame,8) mod(frame,6)
void main()
{	
	int frame = int( mod( (time/slice) ,48) );
	//frame esta entre [0,48)
	int x = frame % 8; // cada frame esta en una x diferent i anira avançant amb el tems 0 1 2 3  
	int y = 5 - frame/8; // cada 8 frames cambiem de linia, i el primer frame esta en a dalt a la esquerra
	// frame[x][y] on x esta entre[0,7] i y entre [0,5] 
	
	vec2 texCoord= vtexCoord*vec2(1.0/8, 1.0/6) //escalamos la textura
			+ vec2(x/8.0,y/6.0);        //sumamos x y del frame que queramos dividido por el escalado para que esté entre 0 y 1
	
	
	fragColor=texture(explosion, texCoord);
  	fragColor*=fragColor.w;
}
