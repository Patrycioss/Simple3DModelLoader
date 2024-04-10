#pragma once


#include <vector>
#include "Vertex.hpp"
#include "../shaders/Texture.hpp"

struct Mesh
{
	std::vector<Vertex> Vertices{};
	std::vector<uint32_t> Indices{};
	std::vector<Texture> Textures{};
};
