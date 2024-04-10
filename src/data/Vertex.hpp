#pragma once

#include <glm/glm.hpp>

struct  Vertex {
	explicit Vertex(const Vertex* pVertex)
	{
		Position = pVertex->Position;
		UV = pVertex->UV;
	}
	
	Vertex()= default;

	glm::vec3 Position{};
	glm::vec2 UV{};
	
	bool operator==(const Vertex& other) const{
		return Position == other.Position && UV == other.UV;
	}
};