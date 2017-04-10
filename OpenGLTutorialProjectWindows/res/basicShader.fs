#version 150

in vec3 dragonColor;

void main(){
	gl_FragColor = vec4(dragonColor, 1.0);
}