#pragma once
#include <vector>

#include "Vertex.hpp"

class Mesh 
{
private:
	unsigned int VAO, VBO, EBO;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> vertexIndices;

public:
	const std::vector<Vertex>& GetVertices();
	explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& vertexIndices);
	void Draw() const;
};
