#include "Triangle.hpp"

#include <glad/gl.h>

#include "../data/Vec2.hpp"

Triangle::Triangle(const Vec2<float> left, const Vec2<float> right, const Vec2<float> top)
{
	const float triangle[9] = {
		left.X, left.Y, 0.0f,
		right.X, right.Y, 0.0f,
		top.X, top.Y, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
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
