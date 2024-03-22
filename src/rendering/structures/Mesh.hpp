#pragma once
#include <vector>

#include "Vertex.hpp"
#include "Texture.hpp"


class Mesh 
{
private:
	unsigned int VAO, VBO, EBO;

	void Setup();
	
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
};
