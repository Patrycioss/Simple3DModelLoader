#pragma once


#include <vector>
#include "Camera.hpp"
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