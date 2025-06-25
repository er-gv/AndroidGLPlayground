#version 300 es
precision mediump float;
uniform mat4 u_mat_mvp;
//uniform mat4 u_mat_mv;

in vec3 aPosition;
out vec3 vPosition;

void main() {
    vec4 pos = u_mat_mvp*vec4(aPosition, 1.0);
    vPosition = aPosition;
    gl_Position = pos;
}