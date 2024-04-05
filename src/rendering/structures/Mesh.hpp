#pragma once
#include <vector>

#include "Vertex.hpp"
#include "Texture.hpp"
#include "ModelTexture.hpp"
#include "../ShaderProgram.hpp"

class Mesh
{
private:
	unsigned int VAO, VBO, EBO;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<ModelTexture> textures;

public:
	explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<ModelTexture>& textures);
	void Draw(const ShaderProgram& shaderProgram) const;
	void SetupMesh();
	void CleanBuffers() const;
};
