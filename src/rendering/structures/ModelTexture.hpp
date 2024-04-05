#pragma once

#include <string>
#include "../../asyncoperations/ReadImageOperation.hpp"
#include "glad/gl.h"

struct ModelTexture{
	unsigned int ID;
	std::string Type;
	std::string Path;
	
//	static ModelTexture LoadFromFile(std::string fileName, std::string directory);
};

inline ModelTexture LoadFromFile(std::string fileName, std::string directory)
{
	std::string path = directory + '/' + fileName;

	ModelTexture texture;
	ReadImageOperation operation = ReadImageOperation{path};

	glGenTextures(1, &texture.ID);
	glBindTexture(GL_TEXTURE_2D, texture.ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	const ReadImageOperation::ImageInfo info = operation.AwaitResult();
	if (info.Data)
	{
		GLenum format = GL_RGB;
		if (info.NrChannels == 1)
			format = GL_RED;
		else if (info.NrChannels == 3)
			format = GL_RGB;
		else if (info.NrChannels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, info.Width, info.Height, 0, format, GL_UNSIGNED_BYTE, info.Data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("Couldn't find data in image with path: %s \n", fileName.c_str());
	}

	return texture;
}
