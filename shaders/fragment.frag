#version 450 core
out vec4 FragColor;

in vec3 VertexPos;
in vec3 TexCoord;
in vec3 Normals;

uniform sampler2DArray tex;

uniform vec3 lightPos;

void main()
{
    vec3 norm = normalize(Normals);
    vec3 lightDir = normalize(lightPos - VertexPos);

    float diff = max(dot(norm, lightDir), 0.0);

    FragColor = texture(tex, TexCoord) * (diff + 0.8);
}
