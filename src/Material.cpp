#include "Material.hpp"

#include <utility>

#include "asyncoperations/ReadImageOperation.hpp"


Material::Material(const ShaderProgram& shaderProgram, std::string texturePath,
                   const WrappingMethod wrappingMethod, const FilteringMethod filteringMethod,
                   const glm::vec4 color) : shaderProgram(shaderProgram)
{
	ReadImageOperation operation = ReadImageOperation{std::move(texturePath)};

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	SetWrappingMethod(wrappingMethod);
	SetFilteringMethod(filteringMethod);

	const ReadImageOperation::ImageInfo info = operation.AwaitResult();
	if (info.Data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, info.Width, info.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, info.Data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	shaderProgram.Use();
	glUniform1i(shaderProgram.GetUniformLocation("texture0"), 0);
	
	glUniform4fv(shaderProgram.GetUniformLocation("color"), 1, &color.r); 
}

void Material::SetWrappingMethod(WrappingMethod wrappingMethod) const
{
	glBindTexture(GL_TEXTURE_2D, texture);

	const GLint method = static_cast<GLint>(wrappingMethod);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, method);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, method);
}

void Material::SetFilteringMethod(FilteringMethod filteringMethod) const
{
	glBindTexture(GL_TEXTURE_2D, texture);

	const GLint method = static_cast<GLint>(filteringMethod);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, method);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, method);
}

void Material::Apply() const
{
	shaderProgram.Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}
