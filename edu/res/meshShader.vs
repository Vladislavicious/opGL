#version 430

layout (location = 0) in vec4 vector_position;
layout (location = 1) in vec3 vector_normal;
layout (location = 2) in vec2 texture_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

void main()
{
    gl_Position = projection * view * model * vector_position;
    FragPos = vec3(model * vector_position);
    Normal = mat3(transpose(inverse(model))) * vector_normal;
    TexCoords = texture_coord;
};
