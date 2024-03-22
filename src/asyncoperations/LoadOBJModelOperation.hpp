#pragma once
#include <OBJ_Loader.h>
#include <thread>
#include <string>

#include "../rendering/structures/OBJModel.hpp"

class LoadOBJModelOperation 
{
private:
	std::thread thread;
	const std::string filePath;
	objl::Loader loader{};

	void LoadModel();;

public:
	explicit LoadOBJModelOperation(const std::string& filePath);

	OBJModel AwaitResult();
};
