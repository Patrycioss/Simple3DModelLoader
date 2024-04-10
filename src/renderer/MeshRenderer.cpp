#include "MeshRenderer.hpp"

void MeshRenderer::Setup()
{
	if (mesh == nullptr)
	{
		printf("No mesh assigned to MeshRenderer! \n");
		return;
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh->Vertices.size() * sizeof(Vertex), &mesh->Vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->Indices.size() * sizeof(unsigned int), &mesh->Indices[0], GL_STATIC_DRAW);

	// Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) nullptr);

	// UV
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, UV));

}

void MeshRenderer::AssignMesh(Mesh* newMesh)
{
	delete mesh;
	mesh = newMesh;
	Setup();
}

void MeshRenderer::Render(const glm::mat4& mvpMatrix)
{
	if (mesh == nullptr)
	{
		return;
	}

	shader.Use();

	const int mvpLocation = shader.GetUniformLocation("MVP");
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvpMatrix[0][0]);

	if (!mesh->Textures.empty())
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(shader.GetUniformLocation("diffuse"), 0);
		glBindTexture(GL_TEXTURE_2D, mesh->Textures[0].ID);
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, mesh->Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

MeshRenderer::~MeshRenderer()
{
	delete mesh;

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
