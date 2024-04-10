#pragma once

#include "../data/Mesh.hpp"

class ModelLoader
{
public:
	static Mesh* LoadModel(const std::string& path);
};
