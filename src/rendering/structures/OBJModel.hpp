#pragma once

#include <OBJ_Loader.h>
#include <vector>

class OBJModel 
{
private:
	std::vector<objl::Mesh> meshes;
	std::vector<objl::Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<objl::Material> materials;

public:
	explicit OBJModel(
		const std::vector<objl::Mesh>& meshes,
		const std::vector<objl::Vertex>& vertices,
		const std::vector<unsigned int>& indices,
		const std::vector<objl::Material>& materials);

	void Test() const;
};
