#include "FileReader.hpp"

#include <fstream>

u_int64 FileReader::lastIndex = 0;
std::unordered_map<u_int64,FileReader::Reader> FileReader::activeReaders{};

void InternalReadFile(const char* path, std::string*& result)
{
	std::ifstream file;

	std::string contents;
	file.open(path);

	std::string line;

	while(std::getline(file, line))
	{
		contents.append(line);
		contents.append("\n");
		line.clear();
	}
	
	file.close();
	result = new std::string(contents);
}


u_int64 FileReader::Read(const char* path)
{
	const u_int64 index = lastIndex++;
	
	activeReaders.insert({index, Reader{}});

	auto& entry = activeReaders.at(index);
	entry.thread = new std::thread(InternalReadFile, path, std::ref(entry.result));

	return index;
}

[[nodiscard]]
std::string FileReader::Result(const u_int64 handle)
{
	return *activeReaders.at(handle).result;
}

bool FileReader::HasHandle(const u_int64 handle)
{
	return activeReaders.contains(handle);
}

void FileReader::Clear(const u_int64 handle)
{
	const auto& reader = activeReaders.at(handle);
	delete reader.result;
	delete reader.thread;
	activeReaders.erase(handle);
}

void FileReader::WaitForRead(const u_int64 handle)
{
	activeReaders.at(handle).thread->join();
}
