#version 410 core
out vec4 FragColor;

in vec2 UV;
out vec3 color;

uniform sampler2D uTextureSampler;

void main()
{
    color = texture(uTextureSampler, UV).rgb;
}