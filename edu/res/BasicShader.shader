#shader vertex
#version 430
layout (location = 0) in vec2 vector_position;
layout (location = 1) in vec3 vector_color;
out vec3 colour;

void main()
{
    gl_Position = vec4(vector_position, 0.0, 1.0);
    colour = vector_color;
};
#shader fragment
#version 430
in vec3 colour;
out vec4 frag_color;

void main()
{
    frag_color = vec4(colour, 1.0);
};
