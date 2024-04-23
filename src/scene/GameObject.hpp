#pragma once


#include <vector>
#include "Component.hpp"
#include "../renderer/Renderer.hpp"
#include "Transform.hpp"
#include "Camera.hpp"

class GameObject
{
private:
	Renderer* renderer = nullptr;

	std::vector<Component*> components{};
	GameObject* parent = nullptr;
	Transform transform{*this};
	
	std::string name{"Just a GameObject"};

protected:
	std::vector<GameObject*> children{};
public:
	const std::vector<GameObject*>& Children = children;
	
	Transform& Transform = transform;

	void AssignRenderer(Renderer* renderer);
	virtual void AddComponent(Component* component);

	void Draw(const Camera& camera) const;
	
	explicit GameObject(std::string name);
	GameObject();
	
	void SetParent(GameObject* newParent);
	GameObject* const& Parent = parent;

	/*Checks whether the given GameObject has already been added.*/
	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);
	
	~GameObject();

	template<class T>
	void RemoveComponentsOfType()
	{
		for (auto iterator = components.begin(); iterator < components.end(); iterator++)
		{
			T* a = dynamic_cast<T*>(*iterator.base());
			if (a != nullptr)
			{
				components.erase(iterator);
				delete a;
			}
		}
	};

	template<class T>
	T* GetComponent()
	{
		for (Component* component: components)
		{
			T* a = dynamic_cast<T*>(component);
			if (a != nullptr)
			{
				return a;
			}
		}
		return nullptr;
	};
};
