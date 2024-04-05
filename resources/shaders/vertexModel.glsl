#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 UV;
uniform mat4 MVP;

void main()
{
    UV = aTexCoords;
    gl_Position = MVP * vec4(aPos, 1.0);
}