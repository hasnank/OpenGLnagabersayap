//#version 120
//
//
//attribute vec3 position;
//attribute vec2 texCoord;
//
//varying vec2 texCoord0;
//
//void main(){
//    gl_Position = vec4(position, 1.0);
//    texCoord0 = texCoord;
//}

#version 120


attribute vec3 position;
attribute vec3 color;

varying vec3 color0;

void main(){
    gl_Position = vec4(position, 1.0);
    color0 = color;
}