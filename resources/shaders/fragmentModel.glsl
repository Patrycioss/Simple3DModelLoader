#version 410 core
out vec4 FragColor;

in vec2 UV;

uniform sampler2D texture0;
uniform vec4 color;

void main()
{
    FragColor = texture(texture0, UV) * color;
//    FragColor = vec4(1,1,1,1);
}