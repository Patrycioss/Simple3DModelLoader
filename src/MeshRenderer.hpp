#pragma once


#include <unordered_map>
#include <set>
#include "structures/Mesh.hpp"
#include "Renderer.hpp"
#include "NewMesh.hpp"

class MeshRenderer : public Renderer
{
private:
	NewMesh* mesh = nullptr;
	
	uint32_t VAO{}, VBO{}, EBO{};
	std::unordered_map<Mesh*, uint32_t> meshes{};
	
	uint32_t indexCount{};

	void RegenerateBuffers()
	{
		std::vector<Vertex> vertices{};
		std::vector<uint32_t> indices{};
		MakeVerticesAndIndices(vertices, indices);
		
		indexCount = indices.size();

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
	}

	void MakeVerticesAndIndices(std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
	{
		std::set<Vertex*> vertices{};

		std::vector<std::_Rb_tree_const_iterator<Vertex*>> iterators{};

		for (std::pair<Mesh*, uint32_t> a: meshes)
		{
			std::vector<unsigned int> indices = a.first->Indices();
			std::vector<Vertex>& meshVertices = a.first->Vertices();

			for (int amount = 0; amount < a.second; amount++){
				for (int vertexIndex = 0; vertexIndex < meshVertices.size(); vertexIndex++)
				{
					Vertex* meshVertex = &meshVertices[vertexIndex];

					auto emplaceResult = vertices.emplace(meshVertex);
					if (emplaceResult.second)
					{
						iterators.push_back(emplaceResult.first);
					} else
					{
						auto findIterator = vertices.find(meshVertex);
						iterators.push_back(findIterator);
					}
				}
			}
		}

		outVertices.reserve(vertices.size());
		std::copy(vertices.begin(), vertices.end(), outVertices.begin());

		for (auto iterator: iterators)
		{
			outIndices.push_back(std::distance(vertices.begin(), iterator));
		}
	}


public:
	void Test(){
		printf("Boogder!");
	}
	
	void Cleanup()
	{
		meshes.clear();
		indexCount = 0;
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	
	void SetMeshes(std::vector<Mesh>& inputMeshes)
	{
		meshes.clear();
		for (Mesh& inputMesh: inputMeshes)
		{
			if (meshes.contains(&inputMesh))
			{
				meshes[&inputMesh]++;
			} else meshes.emplace(&inputMesh, 1);
		}
		
		RegenerateBuffers();
	}
	
	void AssignMesh(NewMesh* newMesh)
	{
		mesh = newMesh;
	}

	void AddMesh(Mesh* newMesh)
	{
		if (meshes.contains(newMesh))
		{
			meshes[newMesh]++;
		} else meshes.emplace(newMesh, 1);


	}

	virtual void Render(const glm::mat4& mvpMatrix) override
	{
		if (mesh == nullptr){
			return;
		}
		
		shader.Use();

		const unsigned int mvpLocation = shader.GetUniformLocation("MVP");
		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvpMatrix[0][0]);

		if (mesh->Textures.size() > 0){
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(shader.GetUniformLocation("diffuse"), 0);
			glBindTexture(GL_TEXTURE_2D, mesh->Textures[0].ID);
		}
		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, mesh->Indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	};
	
	~MeshRenderer(){
		printf("Bye bye");
	}

	void Setup()
	{
		if (mesh == nullptr){
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		// UV
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));
		
	}
};
