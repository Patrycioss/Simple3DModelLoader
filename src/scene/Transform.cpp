#include "Transform.hpp"
#include "GameObject.hpp"

Transform::Transform(GameObject& gameObject)
		: m_GameObject(gameObject)
{}

void Transform::ReCalculateWorldMatrix()
{
	glm::mat4 model(1.0f);

	if (m_GameObject.Parent != nullptr)
	{
		model = m_GameObject.Parent->Transform.worldMatrix;
	}

	model = glm::translate(model, localPosition);
	model = model * glm::mat4_cast(localRotation);
	model = glm::scale(model, localScale);

	worldMatrix = model;

	for (GameObject* child: m_GameObject.Children)
	{
		child->Transform.ReCalculateWorldMatrix();
	}
}

glm::vec3 Transform::Position() const
{
	if (m_GameObject.Parent != nullptr)
	{
		return m_GameObject.Parent->Transform.Position() + localPosition;
	}
	return localPosition;
}

glm::quat Transform::Rotation() const
{
	if (m_GameObject.Parent != nullptr)
	{
		return m_GameObject.Parent->Transform.Rotation() * localRotation;
	}
	return localRotation;
}

glm::vec3 Transform::Scale() const
{
	if (m_GameObject.Parent != nullptr)
	{
		return m_GameObject.Parent->Transform.Scale() + localScale;
	}
	return localPosition;
}

void Transform::SetLocalPosition(glm::vec3 newPosition)
{
	localPosition = newPosition;
	ReCalculateWorldMatrix();
}

void Transform::SetLocalRotation(glm::quat newRotation)
{
	localRotation = newRotation;
	ReCalculateWorldMatrix();
}

void Transform::SetLocalScale(glm::vec3 newScale)
{
	localScale = newScale;
	ReCalculateWorldMatrix();
}
