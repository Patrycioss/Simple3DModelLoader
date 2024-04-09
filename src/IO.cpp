#include "IO.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#include <fstream>

IO::ImageInfo IO::LoadImage(std::string path, bool flipVertical)
{
	ImageInfo imageInfo{};

	stbi_set_flip_vertically_on_load(flipVertical);
	imageInfo.Data = stbi_load(path.c_str(), &imageInfo.Width, &imageInfo.Height, &imageInfo.NrChannels, 0);

	return imageInfo;
}

std::string IO::ReadTextFile(std::string path)
{
	std::ifstream file;

	std::string contents;
	file.open(path);

	std::string line;

	while (std::getline(file, line))
	{
		contents.append(line);
		contents.append("\n");
		line.clear();
	}

	file.close();
	return std::string(contents);
}
