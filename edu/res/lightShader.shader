#shader vertex
#version 430

layout (location = 0) in vec4 vector_position;
layout (location = 1) in vec3 vector_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 colour;

out vec3 Normal;
out vec4 cubeColor;

void main()
{
    gl_Position = projection * view * model * vector_position;
    Normal = vector_normal;
    cubeColor = vec4(colour, 1.0);
};

#shader fragment
#version 430

in vec3 Normal;
out vec4 FragColor;
in vec4 cubeColor;
void main()
{
    FragColor = cubeColor;
}
