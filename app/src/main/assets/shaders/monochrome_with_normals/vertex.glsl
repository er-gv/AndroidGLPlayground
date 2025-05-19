precision mediump float;
uniform mat4 u_mat_mvp;
//uniform mat4 u_mat_mv;

attribute vec3 aPosition;


void main() {
    gl_Position = u_mat_mvp*vec4(aPosition, 0.0);
}