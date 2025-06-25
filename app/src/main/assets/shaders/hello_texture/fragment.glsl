precision mediump float;       	// Set the default precision to medium. We don't need as high of a
								// precision in the fragment shader.
uniform vec3 u_LightPos;       	// The mPosition of the light in eye space.
uniform sampler2D u_Texture;    // The input texture.
uniform vec3 u_FaceNormal;    // The input texture.
uniform mat3 u_NormalsMatrix;
varying vec3 v_Position;
varying vec2 v_TexCoordinate;   // Interpolated texture coordinate per fragment.

// The entry point for our fragment shader.
void main()
{
	// Will be used for attenuation.
    float distance = length(u_LightPos - v_Position);

	// Get a lighting direction vector from the light to the vertex.
    vec3 lightVector = normalize(u_LightPos - v_Position);

	// Calculate the dot product of the light vector and vertex normal. If the normal and light vector are
	// pointing in the same direction then it will get max illumination.
    vec3 t_norm = normalize(-u_NormalsMatrix*u_FaceNormal);
    float diffuse = max(dot(t_norm, lightVector), 0.0);

	// Add attenuation.
    diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance)));

    // Add ambient lighting
    diffuse = clamp(diffuse, 0.601, 1.0);

	// Multiply the color by the diffuse illumination level and texture value to get final output color.
    gl_FragColor = (diffuse*texture2D(u_Texture, v_TexCoordinate));
  }

