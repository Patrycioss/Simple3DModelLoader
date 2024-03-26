#version 410 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aColor;

out vec2 UV;
out vec3 Normal;
out vec3 VertColor;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(aPosition, 1.0);
    UV = aUV;
    Normal = aNormal;
    VertColor = aColor;
}