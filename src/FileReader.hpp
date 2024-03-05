#pragma once
#include <string>
#include <thread>
#include <unordered_map>
#include <_bsd_types.h>


class FileReader 
{
private:
	struct Reader
	{
		std::string* result = nullptr;
		std::thread* thread = nullptr;
	};
	
	static u_int64 lastIndex;
	static std::unordered_map<u_int64,Reader> activeReaders;
	
public:
	static u_int64 Read(const char* path);
	static std::string Result(u_int64 handle);
	static bool HasHandle(u_int64 handle);
	static void Clear(u_int64 handle);
	static void WaitForRead(u_int64 handle);
};
