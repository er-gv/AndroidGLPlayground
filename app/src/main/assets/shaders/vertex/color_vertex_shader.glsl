// A constance represent the combined model/view/projection
//uniform mat4 u_MVPMatrix;

uniform mat4 u_MVPMatrix;

attribute vec3 a_Position;		// Per-vertex mPosition information we will pass in.
attribute vec3 a_Color;			// Per-vertex color information we will pass in.

varying vec3 v_Color;			// This will be passed into the fragment shader.

void main(){
	// Pass through the color.
	v_Color = a_Color;

	gl_Position = u_MVPMatrix*vec4(a_Position, 1.0);
}