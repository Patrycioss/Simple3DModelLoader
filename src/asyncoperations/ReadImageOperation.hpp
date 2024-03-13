#pragma once

#include <thread>

class ReadImageOperation 
{
public:
	struct ImageInfo
	{
		unsigned char* Data;
		const int Width;
		const int Height;
		const int NrChannels;
	};
	
private:
	unsigned char* data{};
	int width{};
	int height{};
	int nrChannels{};
	bool flipVertical{};

	std::thread thread;
	const std::string filePath;

	void ReadFile();

public:
	explicit ReadImageOperation(std::string filePath, bool flipVertically = true);
	[[nodiscard]] ImageInfo AwaitResult();
	void Free() const;
	// ~ReadImageOperation();
};
