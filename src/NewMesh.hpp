#pragma once


#include <vector>
#include "data/Vertex.hpp"
#include "structures/Texture.hpp"

struct NewMesh
{
	std::vector<Vertex> Vertices{};
	std::vector<uint32_t> Indices{};
	std::vector<Texture> Textures{};
};
