#pragma once
#include <vector>

#include "Vertex.hpp"

class Mesh 
{
private:
	unsigned int VAO, VBO;
	std::vector<Vertex> vertices;

public:
	const std::vector<Vertex>& GetVertices();
	explicit Mesh(const std::vector<Vertex>& vertices);
	void Draw() const;
};
