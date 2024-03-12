#version 410 core
out vec4 FragColor;

uniform vec4 newColor;

void main()
{
    FragColor = newColor;
}