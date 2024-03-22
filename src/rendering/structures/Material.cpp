#include "Material.hpp"

#include <utility>

class ShaderProgram;

Material::Material(const ShaderProgram& shaderProgram, const Texture& texture, const glm::vec4 color)
		: shaderProgram(shaderProgram), texture(texture), color(color)
{
	shaderProgram.Use();
	glUniform1i(shaderProgram.GetUniformLocation("texture0"), 0);
	glUniform4fv(shaderProgram.GetUniformLocation("color"), 1, &this->color.r);
}

Material::Material()
{
}

void Material::Apply() const
{
	shaderProgram.Use();
	texture.Bind();
}

const ShaderProgram& Material::Shader() const
{
	return shaderProgram;
}
