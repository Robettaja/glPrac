#version 450 core
#extension GL_ARB_bindless_texture: require

out vec4 FragColor;

in vec3 VertexPos;
in vec2 TexCoord;
in vec3 Normals;

uniform sampler2D tex;
uniform vec3 lightPos;

void main()
{
    vec3 norm = normalize(Normals);
    vec3 lightDir = normalize(lightPos - VertexPos);

    float diff = max(dot(norm, lightDir), 0.0);

    FragColor = texture(tex, TexCoord) * (diff + 0.8);
}
