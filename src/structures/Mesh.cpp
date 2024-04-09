#include "Mesh.hpp"

#include "glad/gl.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
	: vertices(vertices), indices(indices), textures(textures)
{
	SetupMesh();
}

void Mesh::Draw(const ShaderProgram& shaderProgram) const
{
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(shaderProgram.GetUniformLocation("diffuse"), 0);
	glBindTexture(GL_TEXTURE_2D, textures[0].ID);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	
	// UV
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));
	
	
//	// IDs
//	glEnableVertexAttribArray(5);
//	glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));
//
//	// weights
//	glEnableVertexAttribArray(6);
//	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
//	glBindVertexArray(0);

}

void Mesh::CleanBuffers() const
{
//	glDeleteBuffers(vertices.size() * sizeof(Vertex), &VBO);
//	glDeleteBuffers(indices.size() * sizeof(unsigned int), &EBO);
//	glDeleteVertexArrays(1, &VAO);
}

std::vector<unsigned int>& Mesh::Indices()
{
	return indices;
}

std::vector<Vertex>& Mesh::Vertices()
{
	return vertices;
}
