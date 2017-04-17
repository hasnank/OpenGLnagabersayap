#version 120

varying vec3 color0;

//uniform sampler2D diffuse;

void main(){
	gl_FragColor = vec4(color0, 1.0);//texture2D(diffuse, texCoord0); //vec4(dragonColor, 1.0);
}