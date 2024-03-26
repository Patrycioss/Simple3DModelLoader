#include "Mesh.hpp"

#include <cstdio>
#include <glad/gl.h>

const std::vector<Vertex>& Mesh::GetVertices()
{
	return vertices;
}

Mesh::Mesh(const std::vector<Vertex>& vertices)
	: vertices(vertices)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	// Texture Coords Attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);  

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}

void Mesh::Draw() const
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
}
