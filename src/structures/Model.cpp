#include "Model.hpp"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "../ResourceRepo.hpp"

Model::Model(const std::string& path)
	: shaderProgram(ResourceRepo::VertexShader(), ResourceRepo::FragmentShader())
{
	LoadModel(path);
}

void Model::LoadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("ERROR::ASSIMP::%s\n", importer.GetErrorString());
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for(unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		meshes.push_back(ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene));
	}
	
	for(unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for(unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;
		
		// positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		
		// uv coordinates
		if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.UV = vec;
		}
		else
			vertex.UV = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	for(unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		
		// retrieve all indices of the face and store them in the indices vector
		for(unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	std::vector<Texture> diffuseMaps = LoadTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadTextures(aiMaterial* material, aiTextureType type, const std::string& typeName)
{
	std::vector<Texture> textures;
	for(unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString str;
		material->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for(unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if(std::strcmp(textures_loaded[j].Path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if(!skip)
		{   // if texture hasn't been loaded already, load it
			Texture texture = LoadFromFile(str.C_Str(), this->directory);
			texture.Type = typeName;
			texture.Path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}
	return textures;
}

void Model::Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) const
{
	glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
	
	shaderProgram.Use();
	const unsigned int mvpLocation = shaderProgram.GetUniformLocation("MVP");
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
	
	for (const Mesh& mesh : meshes){
		mesh.Draw(shaderProgram);
	}
}

Model::~Model()
{
	for (const Texture& texture : textures_loaded){
		glDeleteTextures(1, &texture.ID);
	}
	
	for (const Mesh& mesh : meshes){
		mesh.CleanBuffers();
	}
}

std::vector<Mesh>& Model::Meshes()
{
	return meshes;
}

ShaderProgram& Model::Shader()
{
	return shaderProgram;
}
