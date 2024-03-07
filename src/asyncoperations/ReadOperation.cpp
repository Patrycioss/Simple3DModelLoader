#include "ReadOperation.hpp"

#include <fstream>
#include <utility>

void ReadOperation::ReadFile()
{
	std::ifstream file;

	std::string contents;
	file.open(filePath);

	std::string line;

	while(std::getline(file, line))
	{
		contents.append(line);
		contents.append("\n");
		line.clear();
	}
	
	file.close();
	result = std::string(contents);
}

ReadOperation::ReadOperation(std::string  filePath)
	: filePath(std::move(filePath))
{
	thread = std::thread(&ReadFile, this);
}

std::string ReadOperation::AwaitResult()
{
	thread.join();
	return result;
}