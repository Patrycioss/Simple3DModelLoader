#include "Scene.hpp"
#include "structures/Model.hpp"

void Scene::AddGameObject(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);

}

void Scene::Draw()
{
	for (const GameObject* gameObject: gameObjects)
	{
		gameObject->Draw(camera);
	}
}

Scene::~Scene()
{
	for (const GameObject* gameObject: gameObjects)
	{
		delete gameObject;

		std::destroy(gameObjects.begin(), gameObjects.end());
	}
}

Scene::Scene(Camera& camera)
		: camera(camera)
{

}