#pragma once
#include <vector>

#include "Mesh.hpp"
#include "assimp/scene.h"
#include "ModelTexture.hpp"

class ModelLoader;

class Model
{
	friend ModelLoader;

private:
	std::vector<ModelTexture> textures_loaded;
	std::string directory;
	bool gammaCorrection;
	std::vector<Mesh> meshes;
	
public:
	explicit Model(const std::string& path, bool gamma = false);
	void Draw(const ShaderProgram& shaderProgram, const glm::mat4& mvp ) const;
	~Model();
	
private:
	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<ModelTexture> LoadTextures(aiMaterial* material, aiTextureType type, const std::string& typeName);
};
