#version 430 core
out vec4 FragColor;
in vec2 UV;

uniform sampler2D diffuse;

void main()
{
    FragColor = texture(diffuse, UV);
}