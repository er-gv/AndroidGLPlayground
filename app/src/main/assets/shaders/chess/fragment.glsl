#version 300 es
precision mediump float;

uniform vec3 uLightDirection;
uniform mat4 u_mat_mvp;
uniform vec3 uFaceNormal;

uniform vec3 uSquareSize;
uniform vec3 uEvenColor;
uniform vec3 uOddColor;


in vec3 vPosition;
out vec4 fragColor;

void main() {
    ivec3 v = ivec3(floor(vPosition/uSquareSize));
    mat3 normals_mat = mat3(u_mat_mvp);
    bool oddity =  (0==((v.x+v.y+v.z)%2));
    vec3 color = (oddity ? uEvenColor : uOddColor);
    vec3 tface = vec3(inverse(transpose(normals_mat))*uFaceNormal);
    float lightFactor = clamp(dot(-uLightDirection,tface), 0.01, 1.0);
    fragColor = vec4(lightFactor*color, 1.0);//lightFactor*color, 1.0);
}