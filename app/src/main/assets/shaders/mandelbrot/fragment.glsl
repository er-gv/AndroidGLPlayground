precision mediump float;       	// Set the default precision to medium. We don't need as high of a
								// precision in the fragment shader.
uniform vec3 u_LightPos;       	// The mPosition of the light in eye space.
uniform sampler2D u_Spectrum;
uniform vec2 u_SpectrumCoords;
uniform vec2 u_juliaSeedPoint;
uniform vec3 u_FaceNormal;    // The input texture.
uniform mat3 u_NormalsMatrix;
uniform float u_exponent;


varying vec3 v_Position;
varying vec2 v_TexCoordinate;


vec2 complex_squared(vec2 c){
    vec2 result;
    result.x = c.x*c.x-c.y*c.y;
    result.y = 2.0*c.x*c.y;
    return result;
}

vec2 projectOntoXY(vec3 point, vec3 normal){
    vec3 result;
    vec3 XNormal = vec3(0.0, 0.0, 1.0);
    vec3 axis = cross(XNormal, point);
    float angle = acos(dot(normal, XNormal));
    result = point*cos(angle)+axis*sin(angle) ;
    return result.xy;
}

float juliaTester(float threashold, int max_itr, vec3 resulotion){

    //first let's see if this pixel is a part of the Julia set. if not it will be black.


    vec2 z = vec2(0.0);
    vec2 c = u_juliaSeedPoint+(
    v_TexCoordinate * pow(0.5, u_exponent)-pow(0.5, 2.0+u_exponent))*pow(0.5, u_exponent);
    int i=0;
    for(i=0; i<max_itr; ++i) {
        vec2 new_z = complex_squared(z)+c;
        if(length(new_z) > threashold){
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
    vec3 t_norm = normalize(u_NormalsMatrix*u_FaceNormal);
    float diffuse = max(dot(t_norm, lightVector), 0.0);

    // Add attenuation.
    diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance)));

    // Add ambient lighting
    diffuse = clamp(diffuse, 0.01, 1.0);
    return diffuse;
}


// The entry point for our fragment shader.
void main()
{
    float diffuse = diffuseCoafficiant();
    float mask = juliaTester(4.0, 100, vec3(0,0,0));
    float spectrumDelta  = u_SpectrumCoords.y - u_SpectrumCoords.x;
    float coord = u_SpectrumCoords.x+mask*spectrumDelta;
	// Multiply the color by the diffuse illumination level and texture value to get final output color.
    gl_FragColor =  diffuse* texture2D(u_Spectrum, vec2(coord, 0.5));
  }

