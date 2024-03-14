#include "Rectangle.hpp"

#include <glad/gl.h>

Rectangle::Rectangle(const Vec2<float> topLeft, const Vec2<float> bottomLeft, const Vec2<float> bottomRight, const Vec2<float> topRight)
{
	const float rectangle[] = {
			// Positions		 // TexCoords
		   topRight.X,    topRight.Y, 0.0f, 1.0f, 1.0f,
		bottomRight.X, bottomRight.Y, 0.0f, 1.0f, 0.0f,
		 bottomLeft.X,  bottomLeft.Y, 0.0f, 0.0f, 0.0f,
			topLeft.X,     topLeft.Y, 0.0f, 0.0f, 1.0f,
	};

	constexpr unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	//TexCoords
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Rectangle::Draw() const
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Rectangle::~Rectangle()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
