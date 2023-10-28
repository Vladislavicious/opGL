#version 430

in vec2 v_TexCoord;
out vec4 frag_color;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    frag_color = texColor;
};
