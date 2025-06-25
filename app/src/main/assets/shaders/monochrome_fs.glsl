#version 120

uniform vec3 vColor;
//varing vec3 vNormal;

void main() {
    gl_FragColor = vec4(vColor*dot(vNormal, gl_position), 1.0);
}