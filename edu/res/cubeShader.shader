#shader vertex
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

#shader fragment
#version 430

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
out vec4 FragColor;


void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    		            light.quadratic * (distance * distance));
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result * attenuation, 1.0);
}
