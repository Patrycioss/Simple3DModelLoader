#pragma once

#include "Renderer.hpp"
#include "../data/Mesh.hpp"

class MeshRenderer : public Renderer
{
private:
	Mesh* mesh = nullptr;
	uint32_t VAO{}, VBO{}, EBO{};
	
	void Setup();

public:
	/* WATCH OUT DELETES EXISTING MESH*/
	void AssignMesh(Mesh* newMesh);
	virtual void Render(const glm::mat4& mvpMatrix) override;;
	~MeshRenderer();
};
