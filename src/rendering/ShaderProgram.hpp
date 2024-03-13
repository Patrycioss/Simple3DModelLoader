#pragma once
#include <string>


class ShaderProgram 
{
private:
	unsigned int ID{};
	
public:
	struct PathContainer
	{
		std::string vertexShaderPath;
		std::string fragmentShaderPath;
	};

	unsigned int& GetID();
	[[nodiscard]] int GetUniformLocation(const char* uniform) const;
	void Use() const;
	explicit ShaderProgram(const PathContainer& pathContainer);
	static std::string MakeShaderPath(const char* shaderName);
};
