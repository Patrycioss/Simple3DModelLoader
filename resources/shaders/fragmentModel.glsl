#version 410 core
out vec4 FragColor;

in vec2 UV;
in vec3 Normal;
in vec3 VertColor;

uniform sampler2D texture0;
uniform vec4 color;

void main()
{
    FragColor = texture(texture0, UV) * color * vec4(VertColor, 1);
//    FragColor = vec4(1,1,1,1);
}