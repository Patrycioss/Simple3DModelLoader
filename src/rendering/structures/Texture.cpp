#include "Texture.hpp"

#include <cstdio>
#include <glad/gl.h>

#include "../../asyncoperations/ReadImageOperation.hpp"

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, textureHandle);
}

const unsigned int& Texture::GetID() const
{
	return textureHandle;
}

Texture::Texture(Texture& texture)
{
	this->textureHandle = texture.textureHandle;
}

Texture Texture::Load(const std::string& path)
{
	Texture texture;
	ReadImageOperation operation = ReadImageOperation{std::move(path)};

	glGenTextures(1, &texture.textureHandle);
	glBindTexture(GL_TEXTURE_2D, texture.textureHandle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	const ReadImageOperation::ImageInfo info = operation.AwaitResult();
	if (info.Data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, info.Width, info.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, info.Data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("Couldn't find data in image with path: %s \n", path.c_str());
	}

	return Texture(texture);
}

Texture::Texture()
{
	
}

void Texture::Cleanup()
{
	glDeleteTextures(1, &textureHandle);
	cleaned = true;
}