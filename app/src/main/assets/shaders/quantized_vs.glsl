//#version 120

attribute vec3 aPosition;
attribute vec3 aColor;

varying vec3 vColor;

uniform mat4 u_MVPMatrix;

void main() {
  gl_Position = u_MVPMatrix*vec4(aPosition, 1.0);
  vColor = aColor;
}