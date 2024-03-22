#include "LoadOBJModelOperation.hpp"

void LoadOBJModelOperation::LoadModel()
{
	loader.LoadFile(filePath);
}

LoadOBJModelOperation::LoadOBJModelOperation(const std::string& filePath): filePath(filePath)
{
	thread = std::thread(&LoadModel, this);
}

OBJModel LoadOBJModelOperation::AwaitResult()
{
	thread.join();
	return OBJModel(loader.LoadedMeshes, loader.LoadedVertices, loader.LoadedIndices, loader.LoadedMaterials);
}
