#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 position_interp;
out vec3 normal_interp;
//out vec4 color_interp;
out vec2 uv_interp;
out vec3 light_pos;

vec3 light_position = vec3(-0.5, -50.0, 1.5);

void main()
{
	mat4 normal = transpose(inverse(model));

	position_interp = vec3(view * model * vec4(aPos, 1.0));
    
    normal_interp = vec3(normal * vec4(aNormal, 0.0));

    //color_interp = vec4(color, 1.0);

    uv_interp = aTexCoords;

    light_pos = vec3(view * vec4(light_position, 1.0));

    TexCoords = aTexCoords;    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}