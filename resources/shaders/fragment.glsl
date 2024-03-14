#version 410 core
out vec4 FragColor;

in vec2 initTexCoord;

uniform sampler2D texture0;
uniform vec4 color;


void main()
{
    FragColor = texture(texture0, initTexCoord) * color;
}