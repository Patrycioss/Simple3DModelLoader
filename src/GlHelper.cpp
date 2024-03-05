#include "GlHelper.hpp"

#include <glad/gl.h>

#include "FileReader.hpp"

constexpr const char* VERTEX_SHADER_PATH = "resources/shaders/vertex.glsl";
constexpr const char* FRAGMENT_SHADER_PATH = "resources/shaders/fragment.glsl";

void DebugShader(const unsigned int shader, const char* name)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		printf("ERROR::SHADER::%s::COMPILATION_FAILED\n%s\n", name, infoLog);
	}
}

void DebugShaderProgram(const unsigned int program)
{
	int  success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if(!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(program, 512, nullptr, infoLog);
		printf("ERROR::SHADERPROGRAM::LINKING_FAILED\n%s\n", std::string(infoLog).c_str());
	}
}

[[nodiscard]]
u_int64 GlHelper::CreateShaderProgram()
{
	const auto vertexHandle = FileReader::Read(VERTEX_SHADER_PATH);
	const auto fragmentHandle = FileReader::Read(FRAGMENT_SHADER_PATH);

	std::string vertexShaderSource;
	std::string fragmentShaderSource;
	
	if (FileReader::HasHandle(vertexHandle))
	{
		FileReader::WaitForRead(vertexHandle);
		vertexShaderSource = FileReader::Result(vertexHandle);
		FileReader::Clear(vertexHandle);
	}

	printf("Loaded vertex shader source:\n %s\n", vertexShaderSource.c_str());
	
	if (FileReader::HasHandle(fragmentHandle))
	{
		FileReader::WaitForRead(fragmentHandle);
		fragmentShaderSource = FileReader::Result(fragmentHandle);
		FileReader::Clear(fragmentHandle);
	}
	
	printf("Loaded fragment shader source:\n %s\n", fragmentShaderSource.c_str());

	const char* vertSSource = vertexShaderSource.c_str();
	const char* fragSSource = fragmentShaderSource.c_str();

	const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertSSource, nullptr);
	glCompileShader(vertexShader);

	DebugShader(vertexShader, "VERTEX");

	const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSSource, nullptr);
	glCompileShader(fragmentShader);

	DebugShader(fragmentShader, "FRAGMENT");
	
	const unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	DebugShaderProgram(shaderProgram);
		
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);  
	
	return shaderProgram;
}
