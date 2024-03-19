#pragma once
#include <string>


class ShaderProgram 
{
private:
	unsigned int ID{};
	
public:
	unsigned int& GetID();
	[[nodiscard]] unsigned int GetUniformLocation(const char* uniform) const;
	void Use() const;
	explicit ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
	explicit ShaderProgram();
	static std::string MakeShaderPath(const char* shaderName);
	~ShaderProgram();
};
