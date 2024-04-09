#pragma once


#include <vector>
#include "Component.hpp"
#include "Renderer.hpp"
#include "Transform.hpp"
#include "Camera.hpp"

class GameObject
{
private:
	
	Renderer* renderer = nullptr;
	Transform transform{};
	
	std::vector<Component*> components{};
	std::vector<GameObject*> children{};
	

public:
	Transform& Transform = transform;
	
	void AssignRenderer(Renderer* renderer);
	void AddComponent(Component* component);

	void Draw(const Camera& camera) const;

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
	virtual ~GameObject();
};
