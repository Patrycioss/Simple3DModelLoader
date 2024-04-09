#pragma once

#include <glm/glm.hpp>

struct  Vertex {
	Vertex(const Vertex* pVertex)
	{
		Position = pVertex->Position;
		UV = pVertex->UV;
	}
	
	Vertex(){
		
	}

	glm::vec3 Position;
	glm::vec2 UV;
	
	bool operator==(const Vertex& other) const{
		return Position == other.Position && UV == other.UV;
	}
};