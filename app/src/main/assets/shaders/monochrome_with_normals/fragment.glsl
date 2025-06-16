precision mediump float;
uniform ivec3 uColor;
uniform vec3 lightDirection;
uniform vec3 uFaceNormal;

void main() {
    float lightFactor = clamp(dot(-lightDirection,uFaceNormal), 0.6, 1.0);
    gl_FragColor = vec4(vec3(uColor)/255.0, 1.0);
}