
precision mediump float;

attribute vec4 a_Position;
varying vec4 v_Position;

uniform mat4 u_matMVP;
uniform mat4 u_mMV;
uniform vec2 u_juliaSeedPoint;

void main() {
    float foo = u_juliaSeedPoint.x*u_juliaSeedPoint.y;
    v_Position = u_mMV * a_Position;
    gl_Position = u_matMVP * a_Position;
}
