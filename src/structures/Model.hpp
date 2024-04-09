#pragma once
#include <vector>

#include "Mesh.hpp"
#include "assimp/scene.h"
#include "Texture.hpp"

class Model
{
private:
	std::vector<Texture> textures_loaded;
	std::string directory;
	std::vector<Mesh> meshes;
	ShaderProgram shaderProgram;
	glm::mat4 modelMatrix = glm::mat4(1.0);
	
public:
	explicit Model(const std::string& path);
	void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) const;
	std::vector<Mesh>& Meshes();
	ShaderProgram& Shader();
	~Model();
	
private:
	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadTextures(aiMaterial* material, aiTextureType type, const std::string& typeName);
	
	
};
