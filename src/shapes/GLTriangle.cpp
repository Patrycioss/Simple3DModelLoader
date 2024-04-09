#include "GLTriangle.hpp"

#include "glad/gl.h"

GLShapes::GLTriangle::GLTriangle(const glm::vec2 left, const glm::vec2 right, const glm::vec2 top)
{
	const float triangle[] = {
		// Positions			//Texture coords
		 left.x,  left.y, 0.0f, 0.0f, 0.0f, 
		  top.x,   top.y, 0.0f, 0.5f, 1.0f,
		right.x, right.y, 0.0f, 1.0f, 0.0f,
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	// Texture Coords Attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);  
	
	glBindVertexArray(0);
}

void GLShapes::GLTriangle::Draw() const
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLShapes::GLTriangle::~GLTriangle()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
