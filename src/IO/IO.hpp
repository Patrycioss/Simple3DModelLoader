#pragma once


#include <string>

class IO
{
public:
	struct ImageInfo
	{
		unsigned char* Data;
		int Width;
		int Height;
		int NrChannels;
	};

public:
	static ImageInfo LoadImage(const std::string& path, bool flipVertical = true);
	
	static std::string ReadTextFile(const std::string& path);
};
