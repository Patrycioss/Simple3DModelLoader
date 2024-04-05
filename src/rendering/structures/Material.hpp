#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

#include "Texture.hpp"
#include "../ShaderProgram.hpp"

class Material
{
private:
	ShaderProgram shaderProgram;
	Texture texture;

public:
	explicit Material(Texture& texture);

	void Apply(const glm::mat4& mvp) const;
	~Material();
};
