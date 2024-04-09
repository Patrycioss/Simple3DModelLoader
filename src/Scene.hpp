#pragma once


#include <vector>
#include "Camera.hpp"
#include "structures/Model.hpp"
#include "MeshRenderer.hpp"
#include "GameObject.hpp"

class Scene
{
	std::vector<GameObject*> gameObjects{};
	Camera& camera;
	
public:
	explicit Scene(Camera& camera);
	void AddGameObject(GameObject* gameObject);
	void Draw();
	~Scene();
};
