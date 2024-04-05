#include "Material.hpp"

#include <glad/gl.h>

class ShaderProgram;

Material::Material(Texture& texture)
		: shaderProgram("resources/shaders/vertexModel.glsl", "resources/shaders/fragmentModel.glsl"), texture(texture)
{
}

void Material::Apply(const glm::mat4& mvp) const
{
	shaderProgram.Use();

	const unsigned int mvpLocation = shaderProgram.GetUniformLocation("MVP");

	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
	
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();
}

Material::~Material()
{
	texture.Cleanup();	

}
