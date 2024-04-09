#pragma once
#include <vector>

#include "../data/Vertex.hpp"
#include "Texture.hpp"
#include "../ShaderProgram.hpp"

class Mesh
{
private:
	unsigned int VAO, VBO, EBO;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

public:
	std::vector<unsigned int>& Indices();
	std::vector<Vertex>& Vertices();
	
	explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
	void Draw(const ShaderProgram& shaderProgram) const;
	void SetupMesh();
	void CleanBuffers() const;
};
