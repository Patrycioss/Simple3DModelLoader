#include "GameObject.hpp"
#include "Camera.hpp"

GameObject::~GameObject()
{
	delete renderer;

	for (const auto& item: components)
	{
		delete item;
	}
}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);

	Transform.position = glm::vec3(0, 0, 0);
}

void GameObject::Draw(const Camera& camera) const
{
	if (renderer != nullptr)
	{
		renderer->Render(camera.projectionMatrix * camera.GetViewMatrix() * transform.modelMatrix);
	}

	for (const GameObject* child: children)
	{
		child->Draw(camera);
	}
}

void GameObject::AssignRenderer(Renderer* pRenderer)
{
	renderer = pRenderer;
}
