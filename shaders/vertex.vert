#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

out vec2 TexCoord;

uniform mat4 projectionView;
uniform mat4 model;

vec4 CalculateviewProjection() {
    return projectionView * model * vec4(aPos, 1.0);
}

void main()
{
    gl_Position = CalculateviewProjection();
    TexCoord = aTexCoord;
}
