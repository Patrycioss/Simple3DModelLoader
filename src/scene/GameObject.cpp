#include <algorithm>
#include <utility>
#include "GameObject.hpp"
#include "Camera.hpp"

GameObject::~GameObject()
{
	delete renderer;

	for (const auto& item: components)
	{
		delete item;
	}
	
	for (GameObject* gameObject : children){
		delete gameObject;
	}
}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);
}

void GameObject::Draw(const Camera& camera) const
{
	if (renderer != nullptr)
	{
		renderer->Render(camera.projectionMatrix * camera.GetViewMatrix() * transform.WorldMatrix);
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

void GameObject::SetParent(GameObject* newParent)
{
	if (parent != nullptr){
		parent->RemoveChild(this);
	}
	
	parent = newParent;
	
	if (parent != nullptr){
		parent->AddChild(this);
	}
}

void GameObject::RemoveChild(GameObject* child)
{
	auto found = std::find(children.begin(), children.end(), child);
	
	if (found != children.end()){
		children.erase(found);
	}
}

void GameObject::AddChild(GameObject* child)
{
	auto found = std::find(children.begin(), children.end(), child);

	if (found == children.end()){
		children.push_back(child);
	}
}

GameObject::GameObject() = default;

GameObject::GameObject(std::string name)
	: name(std::move(name))
{
	
}
