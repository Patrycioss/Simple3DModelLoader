#include "OBJModel.hpp"

OBJModel::OBJModel(const std::vector<objl::Mesh>& meshes, const std::vector<objl::Vertex>& vertices, const std::vector<unsigned int>& indices,
	const std::vector<objl::Material>& materials):
	meshes(meshes), vertices(vertices), indices(indices), materials(materials)
{}

void OBJModel::Test() const
{
	for (objl::Mesh m: meshes)
	{
		printf("%s", m.MeshName.c_str());
	}
}
