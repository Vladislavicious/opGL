#version 430

in vec3 Normal;
out vec4 FragColor;
in vec4 cubeColor;
void main()
{
    FragColor = cubeColor;
}
