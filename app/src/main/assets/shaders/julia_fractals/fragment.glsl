precision mediump float;


//uniform mat4 u_MVMatrix;
uniform mat4 u_MVPMatrix;		// A constant representing the combined model/view/projection matrix.
uniform sampler2D u_Spectrum;
//uniform mat4 u_MVMatrix;
//uniform mat4 u_NormalsMatrix;

//uniform vec3 u_faceNormal;
//uniform vec3 u_LightPos;
//uniform sampler2D u_Spectrum;    // The spectrum texture.
//uniform vec2 u_SpectrumCoords;
//uniform vec2 u_juliaSeedPoint;

varying vec3 v_Position;

/*
vec2 complex_squared(vec2 c){
    vec2 result;
    result.x = c.x*c.x-c.y*c.y;
    result.y = 2.0*c.x*c.y;
    return result;
}

float juliaTester(float threashold, int max_itr, vec3 resulotion){

	//first let's see if this pixel is a part of the Julia set. if not it will be black.

	vec2 c = u_juliaSeedPoint;
    vec2 z = vec2(v_Position.x, v_Position.y);
    int i;
    float normelizedDist = 0.0;//
    for(i=0; i<max_itr; i++) {
        vec2 new_z = (complex_squared(z))+c;
        normelizedDist = (new_z.x * new_z.x) + (new_z.y * new_z.y);
		if(normelizedDist > threashold){
        	break;
        }//
        z = new_z;

    }
    if(i==max_itr) return 1.0;
    return float(i)/float(max_itr);

}
// The entry point for our fragment shader.

float diffuseCoafficiant(){
    // Will be used for attenuation.
    float distance = length(u_LightPos - v_Position);

    // Get a lighting direction vector from the light to the vertex.
    vec3 lightVector = normalize(u_LightPos - v_Position);

    // Calculate the dot product of the light vector and vertex normal. If the normal and light vector are
    // pointing in the same direction then it will get max illumination.
    float diffuse = max(dot(normalize(u_faceNormal), lightVector), 0.0);

    // Add attenuation.
    diffuse = diffuse * (1.0 / (1.0 + (0.10 * distance)));

    // Add ambient lighting
    diffuse = diffuse + 0.5;
    return diffuse;
}
*/
void main(){

    //gl_FragColor = diffuse* texture2D(u_Texture, v_TexCoordinate);

    //float mask = juliaTester(4.0, 65, vec3(0,0,0));
    //float coord = u_SpectrumCoords.x+mask*u_SpectrumCoords.y;
  	gl_FragColor = vec4(1.0, 0.2, 0.8, 1.0);
    //texture2D(u_Spectrum, vec2(coord, 0)) *diffuseCoafficiant();//
}

