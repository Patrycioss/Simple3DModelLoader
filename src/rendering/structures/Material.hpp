#pragma once

#include <glm/glm.hpp>

#include "Texture.hpp"
#include "../ShaderProgram.hpp"

class Material
{
private:
	ShaderProgram shaderProgram;
	Texture texture{};
	glm::vec4 color{};

public:
	Material(const ShaderProgram& shaderProgram,
		const Texture& texture
		, glm::vec4 color = {1,1,1,1});

	Material();
	void Apply() const;
	const ShaderProgram& Shader() const;
};