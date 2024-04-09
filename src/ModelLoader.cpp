#include <set>
#include "ModelLoader.hpp"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

void LoadTextures(aiMaterial* material, aiTextureType type, const std::string& typeName,
                  std::string& directory, std::vector<Texture>& textures)
{
	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString str;
		material->GetTexture(type, i, &str);

		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		auto findIt = std::find_if(textures.begin(), textures.end(), [&](const Texture& texture)
		{
			return texture.Path == str.C_Str();
		});


		if (findIt == textures.end())
		{
			Texture texture = LoadFromFile(str.C_Str(), directory);
			texture.Type = typeName;
			texture.Path = str.C_Str();
			textures.push_back(texture);
		}
	}
}

void ProcessMesh(aiMesh* mesh, const aiScene* scene, std::string& directory, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices,
                 std::vector<Texture>& textures)
{
	std::vector<uint32_t> indicesInProcess;

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indicesInProcess.push_back(face.mIndices[j]);
	}

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;

		// positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		// uv coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.UV = vec;
		} else
			vertex.UV = glm::vec2(0.0f, 0.0f);

		uint32_t newIndex;

//		auto findIt = std::find(vertices.begin(), vertices.end(), vertex);
//		
//		if (findIt == vertices.end()){
//			vertices.push_back(vertex);
//			newIndex = vertices.size()-1;
//		}
//		else {
//			newIndex = findIt - vertices.begin();
//		}

		vertices.push_back(vertex);
		newIndex = vertices.size() - 1;

		for (int indexIndex = 0; indexIndex < indicesInProcess.size(); indexIndex++)
		{
			if (indicesInProcess[indexIndex] == i)
			{
				indicesInProcess[indexIndex] = newIndex;
			}
		}
	}

	indices.reserve(indices.size() + indicesInProcess.size());
	indices.insert(indices.end(), indicesInProcess.begin(), indicesInProcess.end());

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	LoadTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", directory, textures);

}

void ProcessNode(aiNode* node, const aiScene* scene, std::string& directory, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices,
                 std::vector<Texture>& textures)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene, directory, vertices, indices, textures);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene, directory, vertices, indices, textures);
	}
}


NewMesh* ModelLoader::LoadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path,
	                                         aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("ERROR::ASSIMP::%s\n", importer.GetErrorString());
		return nullptr;
	}

	std::string directory = path.substr(0, path.find_last_of('/'));

	std::vector<Texture> textures{};
	std::vector<Vertex> vertices{};
	std::vector<uint32_t> indices{};

	ProcessNode(scene->mRootNode, scene, directory, vertices, indices, textures);


	return new NewMesh{vertices, indices, textures};
}
