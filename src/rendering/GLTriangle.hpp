#pragma once
#include <glm/vec2.hpp>

namespace GLShapes
{
	class GLTriangle 
	{
	private:
		unsigned int VBO{};
		unsigned int VAO{};

	public:
		explicit GLTriangle(glm::vec2 left, glm::vec2 right, glm::vec2 top);
		void Draw() const;
		~GLTriangle();
	};
}
