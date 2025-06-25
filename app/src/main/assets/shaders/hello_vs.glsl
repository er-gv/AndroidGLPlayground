//#version 120


uniform mat4 u_mat_mvp;
//uniform mat3 u_mat_mv;


attribute vec3 aPosition;
attribute vec3 aColor;
//attribute vec2 aTexCoord;


varying vec4 vColor;


void main() {
    gl_Position = u_mat_mvp*vec4(aPosition, 0.0);
    vColor = vec4(aColor, 1.0);
}