#include "Mesh.hpp"

#include <cstdio>
#include <glad/gl.h>

const std::vector<Vertex>& Mesh::GetVertices()
{
	return vertices;
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& vertexIndices)
	: vertices(vertices), vertexIndices(vertexIndices)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	const unsigned int sizy = sizeof(GL_UNSIGNED_INT) * vertexIndices.size();
	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_UNSIGNED_INT) * vertexIndices.size(), vertexIndices.data(), GL_STATIC_DRAW);

	constexpr unsigned int stride = 11 * sizeof(float);
	
	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	// Texture Coords Attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Normal Attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// Color Attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);

	// Do after unbinding VAO otherwise it's not linked to VAO
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	GLenum err;
	while((err = glGetError()) != GL_NO_ERROR)
	{
		printf("Error!!!!: %u", err);
	}
}

void Mesh::Draw() const
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
