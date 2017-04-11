#version 150


attribute vec3 position;
in vec3 color;
out vec3 dragonColor;

void main(){
	dragonColor = color;
	gl_Position = vec4(position, 1.0);
}