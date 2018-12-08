#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

in vec3 position_interp;
in vec3 normal_interp;
//in vec4 color_interp;
in vec2 uv_interp;
in vec3 light_pos;

vec4 ambient_color = vec4(0.1, 0.1, 0.1, 1.0);
vec4 diffuse_color = vec4(0.1, 0.08, 0.06, 1.0);
vec4 specular_color = vec4(0.8, 0.5, 0.9, 1.0);
float phong_exponent = 128.0;

uniform sampler2D texture_diffuse1;

void main()
{    
	vec3 N, // Interpolated normal for fragment
         L, // Light-source direction
         V, // View direction
         H; // Half-way vector
		 
	vec3 L2, H2;

    // Compute Lambertian lighting Id
    N = normalize(normal_interp);

    L = (light_pos - position_interp);
    L = normalize(L);

    float Id = max(dot(N, L), 0.0);
    
    // Compute specular term for Blinn-Phong shading
    //V = (eye_position - position_interp);
    V = - position_interp; // Eye position is (0, 0, 0) in view coordinates
    V = normalize(V);

    //H = 0.5*(V + L); // Halfway vector
    H = (V + L); // Halfway vector
    H = normalize(H);

    float spec_angle_cos = max(dot(N, H), 0.0);
    float Is = pow(spec_angle_cos, phong_exponent);

    // Retrieve texture value
    vec4 pixel = texture(texture_diffuse1, uv_interp);
	vec4 diff = normalize(pixel + diffuse_color);
	vec4 spec = normalize(pixel + specular_color);

	FragColor = texture(texture_diffuse1, TexCoords) + Id*diffuse_color + Is*spec + ambient_color;

    // Use texture in determining fragment colour
    //gl_FragColor = normalize(FragColor + ambient_color + Id*diff + Is*spec);

    
}