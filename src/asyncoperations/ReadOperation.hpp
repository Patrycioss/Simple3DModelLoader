#pragma once
#include <thread>


class ReadOperation 
{
private:
	std::thread thread;
	std::string result{};
	const std::string filePath;

	void ReadFile();

public:
	explicit ReadOperation(std::string  filePath);
	[[nodiscard]] std::string AwaitResult(); 
};
