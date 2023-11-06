#version 430

layout (location = 0) in vec4 vector_position;
layout (location = 1) in vec3 vector_normal;
layout (location = 2) in vec2 vector_tex;

out vec3 colour;
uniform mat4 u_MVP;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vector_position;
    colour = vec3(1.0, 0.0, 0.0);
};
