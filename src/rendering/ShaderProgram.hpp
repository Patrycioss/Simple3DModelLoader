#pragma once
#include <string>


class ShaderProgram 
{
private:
	unsigned int ID{};
	
public:
	unsigned int& GetID();
	[[nodiscard]] int GetUniformLocation(const char* uniform) const;
	void Use() const;
	explicit ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
	static std::string MakeShaderPath(const char* shaderName);
	~ShaderProgram();
};
