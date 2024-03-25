#pragma once
#include <string>
#include <glad/gl.h>

class Texture
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
	unsigned int textureHandle{};

public:
	explicit Texture(std::string path,
	                 WrappingMethod wrappingMethod = WrappingMethod::Repeat,
	                 FilteringMethod filteringMethod = FilteringMethod::Linear
	);

	explicit Texture();

	void SetWrappingMethod(WrappingMethod wrappingMethod) const;
	void SetFilteringMethod(FilteringMethod filteringMethod) const;
	void Bind() const;
	const unsigned int& GetID() const;
};