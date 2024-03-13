#include "Triangle.hpp"

#include <glad/gl.h>

#include "../data/Vec2.hpp"

Triangle::Triangle(const Vec2<float> left, const Vec2<float> right, const Vec2<float> top)
{
	const float triangle[] = {
		// Positions			//Colors		//Texture coords
		 left.X,  left.Y, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 
		right.X, right.Y, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		  top.X,   top.Y, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	// Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture Coords Attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(2);  
	
	glBindVertexArray(0);
}

void Triangle::Draw() const
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

Triangle::~Triangle()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
