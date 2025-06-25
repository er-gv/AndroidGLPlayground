precision mediump float;

//uniform vec3 uLightDirection;
//uniform vec3 uFaceNormal;
uniform vec3 uColor;

void main() {
    //float lightFactor = clamp(dot(-uLightDirection, uFaceNormal), 0.8, 1.0);
    gl_FragColor = vec4(uColor, 1.0);
}