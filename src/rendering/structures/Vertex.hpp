#pragma once

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 Position{};
	glm::vec2 UV{};
	glm::vec3 Normal{};
	glm::vec3 Color{1,1,1};
};