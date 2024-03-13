#version 410 core
out vec4 FragColor;

in vec3 initColor;
in vec2 initTexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;


void main()
{
    FragColor = mix(texture(texture1, initTexCoord), texture(texture2, initTexCoord), 0.2) * vec4(initColor, 1.0);
}