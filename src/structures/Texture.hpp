#pragma once

#include <string>
#include <cstring>
#include "glad/gl.h"
#include "../IO.hpp"

struct Texture
{
	unsigned int ID;
	std::string Type;
	std::string Path;
	
	bool operator==(const Texture& other) const{
		return std::strcmp(other.Path.data(), Path.c_str()) == 0;
	}
	
	bool operator <(const Texture& other) const{
		return ID < other.ID;
	}
};

inline Texture LoadFromFile(std::string fileName, std::string directory)
{
	std::string path = directory + '/' + fileName;

	Texture texture;
	IO::ImageInfo image = IO::LoadImage(path);

	glGenTextures(1, &texture.ID);
	glBindTexture(GL_TEXTURE_2D, texture.ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (image.Data)
	{
		GLenum format = GL_RGB;
		if (image.NrChannels == 1)
			format = GL_RED;
		else if (image.NrChannels == 3)
			format = GL_RGB;
		else if (image.NrChannels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, image.Width, image.Height, 0, format, GL_UNSIGNED_BYTE, image.Data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
	{
		printf("Couldn't find data in image with path: %s \n", fileName.c_str());
	}

	return texture;
}
