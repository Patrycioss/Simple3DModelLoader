﻿#include "ReadImageOperation.hpp"

#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/stb/stb_image.h"

void ReadImageOperation::ReadFile()
{
	stbi_set_flip_vertically_on_load(flipVertical);
	data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
}

ReadImageOperation::ReadImageOperation(std::string filePath, const bool flipVertically)
	: flipVertical(flipVertically), filePath(std::move(filePath))
{
	thread = std::thread(&ReadFile, this);
}

ReadImageOperation::ImageInfo ReadImageOperation::AwaitResult()
{
	thread.join();
	return {data, width, height, nrChannels};
}

ReadImageOperation::~ReadImageOperation()
{
	stbi_image_free(data);
}