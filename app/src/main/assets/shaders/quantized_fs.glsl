//#version 120
precision mediump float;

uniform float uQuanta;
varying vec3 vColor;

void main() {
  vec3 quantized = floor(vColor*uQuanta)/uQuanta;
  gl_FragColor = vec4(quantized, 1.0);
}