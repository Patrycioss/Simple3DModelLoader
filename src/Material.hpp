#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>

#include "rendering/ShaderProgram.hpp"

class Material
{
public:
	enum class WrappingMethod
	{
		Repeat = GL_REPEAT,
		MirroredRepeat = GL_MIRRORED_REPEAT,
		ClampEdge = GL_CLAMP_TO_EDGE,
		ClampBorder = GL_CLAMP_TO_BORDER
	};

	enum class FilteringMethod
	{
		Nearest = GL_NEAREST, // No smoothing
		Linear = GL_LINEAR // Pixel smoothing
	};

private:
	ShaderProgram shaderProgram;
	unsigned int texture{};

public:
	Material(const ShaderProgram& shaderProgram, std::string texturePath,
	         WrappingMethod wrappingMethod = WrappingMethod::Repeat, FilteringMethod filteringMethod = FilteringMethod::Linear,
	         glm::vec4 color = {1,1,1,1}
	);
	void SetWrappingMethod(WrappingMethod wrappingMethod) const;
	void SetFilteringMethod(FilteringMethod filteringMethod) const;
	void Apply() const;
};
