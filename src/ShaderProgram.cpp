#include "ShaderProgram.hpp"
#include "FileReader.hpp"

#include <glad/gl.h>
#include <utility>

constexpr const char* SHADER_FOLDER_PATH = "resources/shaders/";
constexpr const char* SHADER_EXTENSION = ".glsl";

class ShaderProgramException final : public std::exception
{
	const char* message;

public:
	explicit ShaderProgramException(const std::string& message)
	{
		this->message = message.c_str();
	}
	
	[[nodiscard]] const char* what() const noexcept override
	{
		return message;
	}
};

void DebugShader(const unsigned int shader, const char* name)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		throw ShaderProgramException("Failed to compile shader '" + std::string(name) + "' with info: \n'" + std::string(infoLog) +"'\n");
	}
}

void DebugShaderProgram(const unsigned int program)
{
	int  success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	// if(!success)
	// {
	// 	char infoLog[512];
	// 	glGetShaderInfoLog(program, 512, nullptr, infoLog);
	// 	throw ShaderProgramException("Failed to link shader program with info: \n'" + std::string(infoLog) +"'\n");
	// }
}

unsigned int& ShaderProgram::GetID()
{
	return ID;
}

ShaderProgram::ShaderProgram(const PathContainer& pathContainer)
{
	const auto vertexHandle = FileReader::Read(pathContainer.vertexShaderPath);
	const auto fragmentHandle = FileReader::Read(pathContainer.fragmentShaderPath);

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
	
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	DebugShaderProgram(ID);
		
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

[[nodiscard]]
std::string ShaderProgram::MakeShaderPath(const char* shaderName)
{
	std::string path = std::string(SHADER_FOLDER_PATH);
	path.append(shaderName);
	path.append(SHADER_EXTENSION);
	return path;
}
