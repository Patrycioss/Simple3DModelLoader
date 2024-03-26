#version 410 core
layout (location = 0) in vec3 aVertex;
layout (location = 1) in vec2 aUV;
//layout (location = 2) in vec3 aNormal;


out vec2 UV;
uniform mat4 MVP;

//out vec3 Normal;

void main()
{
    gl_Position = MVP * vec4(aVertex, 1.0);
    UV = aUV;
//    Normal = aNormal;
}