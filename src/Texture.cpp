#include "Texture.hpp"

#include "asyncoperations/ReadImageOperation.hpp"

Texture::Texture(std::string path,
                 const WrappingMethod wrappingMethod,
                 const FilteringMethod filteringMethod
)
{
	ReadImageOperation operation = ReadImageOperation{std::move(path)};

	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	SetWrappingMethod(wrappingMethod);
	SetFilteringMethod(filteringMethod);

	const ReadImageOperation::ImageInfo info = operation.AwaitResult();
	if (info.Data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, info.Width, info.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, info.Data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

Texture::Texture()
{
}

void Texture::SetWrappingMethod(WrappingMethod wrappingMethod) const
{
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	const GLint method = static_cast<GLint>(wrappingMethod);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, method);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, method);
}

void Texture::SetFilteringMethod(FilteringMethod filteringMethod) const
{
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	const GLint method = static_cast<GLint>(filteringMethod);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, method);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, method);
}

void Texture::Bind() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
}