#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 initColor;
out vec2 initTexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    initColor = aColor;
    initTexCoord = aTexCoord;
}