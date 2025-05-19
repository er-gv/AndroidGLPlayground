precision mediump float;
uniform vec3 uColor;
//uniform vec3 lightDirection;
uniform vec3 uFaceNormal;

void main() {
    //float lightFactor = dot(-lightDirection,uFaceNormal);
    gl_FragColor = vec4(uColor, 1.0);
}