#version 120

uniform vec3 uColor;
//varing vec3 vNormal;

void main() {
    gl_FragColor = vec4(uColor, 1.0);
}