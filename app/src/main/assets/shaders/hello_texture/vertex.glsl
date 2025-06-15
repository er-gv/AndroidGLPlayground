uniform mat4 u_MVPMatrix;		// A constant representing the combined model/view/projection matrix.      		       
//uniform mat4 u_MVMatrix;		// A constant representing the combined model/view matrix.
		  			
attribute vec3 a_Position;		// Per-vertex mPosition information we will pass in.
//attribute vec3 a_Normal;		// Per-vertex normal information we will pass in.
attribute vec2 a_TexCoordinate; // Per-vertex texture coordinate information we will pass in. 		
		  
//varying vec3 v_Position;		// This will be passed into the fragment shader.
//varying vec3 v_Normal;			// This will be passed into the fragment shader.
varying vec2 v_TexCoordinate;   // This will be passed into the fragment shader.    		
		  
// The entry point for our vertex shader.  
void main()                                                 	
{                                                         
	// Pass through the texture coordinate.
	v_TexCoordinate = a_TexCoordinate;                                      
	
	// Transform the normal's orientation into eye space.
    //v_Normal = vec3(u_MVMatrix * vec4(a_Normal, 0.0));
	gl_Position = (u_MVPMatrix * vec4(a_Position, 1.0));
}                                                          