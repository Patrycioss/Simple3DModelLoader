#pragma once

#include <OBJ_Loader.h>
#include <vector>

#include "../ShaderProgram.hpp"

struct OBJTexture
{
	objl::Material material;
	unsigned int handle{};

	explicit OBJTexture(objl::Material material);
};

class OBJModel 
{
private:
	std::vector<objl::Mesh> meshes;
	std::vector<objl::Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<OBJTexture> textures{};

	void SetupMesh();

	unsigned int VAO, VBO, EBO;

public:
	explicit OBJModel(
		const std::vector<objl::Mesh>& meshes,
		const std::vector<objl::Vertex>& vertices,
		const std::vector<unsigned int>& indices,
		const std::vector<objl::Material>& materials);
	
	void Test() const;
	void Draw(ShaderProgram& shaderProgram);
};
