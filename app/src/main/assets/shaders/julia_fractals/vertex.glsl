precision mediump float;

//uniform mat4 u_MVMatrix;
uniform mat4 u_MVPMatrix;		// A constant representing the combined model/view/projection matrix.

attribute vec4 a_Position;		// Per-vertex mPosition information we will pass in.

varying vec3 v_Position;		// This will be passed into the fragment shader.

// The entry point for our vertex shader.  
void main()
{
    // Transform the vertex into eye space.
    vec4 pos4 = u_MVPMatrix * a_Position;
    v_Position = vec3(pos4);


    gl_Position = u_MVPMatrix * a_Position;
}                                                          