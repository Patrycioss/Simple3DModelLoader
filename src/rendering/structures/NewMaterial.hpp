#pragma once
#include <string>
#include <glad/gl.h>

#include "../../asyncoperations/ReadImageOperation.hpp"


class NewMaterial 
{
public:
	enum TextureType
	{
		Ambient = 0,
		Diffuse = 1,
		Specular = 2,
		Bump = 3,
	};
	
private:

	unsigned int textures[4]{0,0,0,0};
	bool texturesGiven[4]{false, false, false, false};
	
	void GenerateTexture(const TextureType textureType, const std::string& path)
	{
		ReadImageOperation operation = ReadImageOperation(path);

		glGenTextures(1, &textures[textureType]);
		glBindTexture(GL_TEXTURE_2D, textures[textureType]);

		const ReadImageOperation::ImageInfo info = operation.AwaitResult();
		if (info.Data)
		{
			// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
			// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
			// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info.Width, info.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, info.Data);

			glGenerateMipmap(GL_TEXTURE_2D);

			glActiveTexture(GL_TEXTURE0 + (int) textureType);
			glBindTexture(GL_TEXTURE_2D, textures[(int) textureType]);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			texturesGiven[(int) textureType] = true;
		}
		else
		{
			printf("Couldn't load texture with path: %s ! \n", path.c_str());
		}
	}
	
public:
	void SetTexture(const TextureType textureType, const std::string& path)
	{
		std::string newPath("resources/models/");
		newPath.append(path);
		printf("Path: %s \n", newPath.c_str());

		GenerateTexture(textureType, newPath);
	}

	void Apply() const
	{
		// Ambient
		if (texturesGiven[0])
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textures[0]);
		}
		
		// Diffuse
		if (texturesGiven[1])
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures[1]);
		}
		
		// Specular
		if (texturesGiven[2])
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, textures[2]);
		}
		
		// Normal
		if (texturesGiven[3])
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, textures[3]);
		}

		glActiveTexture(GL_TEXTURE0);
	}
};
