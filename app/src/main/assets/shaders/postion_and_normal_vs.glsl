#version 120

attribute vec4 aPosition;
attribute vec3 aNormal;

varying vec3 vNormal;

uniform mat3 mat_MV;
uniform mat4 mat_MVP;
void main() {
    gl_Position = mat_MVP*aPosition;
    vNormal = mat_MV*aNormal;

}