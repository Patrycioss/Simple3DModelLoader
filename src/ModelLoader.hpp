#pragma once


#include "structures/Mesh.hpp"
#include "NewMesh.hpp"

class ModelLoader
{
public:
	static NewMesh* LoadModel(std::string path);
};
