#version 130

// Attributes passed from the vertex shader
in vec3 position_interp;
in vec3 normal_interp;
in vec3 light_pos;

// General constants
float pi = 3.1415926535897932;

// Blue metal
vec3 diffuse_color = vec3(0.0, 0.0, 0.0);
vec3 specular_color = vec3(0.2, 0.2, 0.95);

// Copper
//vec3 diffuse_color = vec3(0.0, 0.0, 0.0);
//vec3 specular_color = vec3(0.95, 0.64, 0.54);

float roughness = 0.5;
float light_intensity = 1.0*pi;

// Uniform (global) buffer
uniform samplerCube env_map;


void main() 
{
    // Physically-based shading model

    vec3 N, // Interpolated normal for fragment
         L, // Light-source direction
         V, // View direction
         H; // Half-way vector

    // Initialize input quantities
    N = normalize(normal_interp);

    L = (light_pos - position_interp);
    L = normalize(L);

    // V = (eye_position - position_interp);
    V = - position_interp; // Eye position is (0, 0, 0) in view coordinates
    V = normalize(V);

    //H = 0.5*(V + L); // Halfway vector
    H = (V + L); // Halfway vector
    H = normalize(H);

    // Compute useful quantities
    float NH = max(dot(N, H), 0.0);
    float LH = max(dot(L, H), 0.0);
    float NL = max(dot(N, L), 0.0);

    // Compute shading model
    // Diffuse term (subsurface scattering)
    vec3 diffuse = diffuse_color / pi;

    // Microfacet geometry
    // Fresnel term
    vec3 fresnel = specular_color + (vec3(1.0, 1.0, 1.0) - specular_color)*pow(1 - LH, 5.0);
    // GGX distribution function
    float denom = NH*NH*(roughness*roughness - 1.0) + 1.0;
    float ndist = roughness / (pi*denom*denom);
    // Microfacet term: assume implicit geometry function
    vec3 mfacet = fresnel * (ndist / 4.0);

    // Full illumination
    vec3 illum = (diffuse + mfacet)*light_intensity*NL;

    // Compute indirect lighting
    // Reflection vector
    vec3 Lr = 2.0 * NL * N - L;
    // Query environment map
    vec4 il = texture(env_map, Lr);
    // Add pixel value to the illumination
    // Modulate influence of environment light by some constant
    illum += 0.7*il.xyz;
 
    // Assign illumination to the fragment
    gl_FragColor = vec4(illum, 1.0);
}
