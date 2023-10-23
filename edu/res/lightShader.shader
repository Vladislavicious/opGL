#shader vertex
#version 430

layout (location = 0) in vec4 vector_position;
layout (location = 1) in vec3 vector_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 Normal;

void main()
{
    gl_Position = projection * view * model * vector_position;
    Normal = vector_normal;
};

#shader fragment
#version 430

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0);
}
