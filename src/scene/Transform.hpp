#pragma once


#include <glm/vec3.hpp>
#include<glm/gtc/quaternion.hpp>
#include <vector>

class GameObject;

class Transform
{
private:
	glm::mat4 worldMatrix = glm::mat4(1.0f);
	
	GameObject& m_GameObject;

	glm::vec3 localPosition{0,0,0};
	glm::quat localRotation{0,0,0,1};
	glm::vec3 localScale = glm::vec3(1,1,1);
	
	void ReCalculateWorldMatrix();
	
public:
	const glm::mat4& WorldMatrix = worldMatrix;
	
	explicit Transform(GameObject& gameObject);
	Transform operator=(Transform transform) = delete;

	[[nodiscard]] glm::vec3 Position() const;
	[[nodiscard]] glm::quat Rotation() const;
	[[nodiscard]] glm::vec3 Scale() const;
	
	const glm::vec3& LocalPosition = localPosition;
	const glm::quat& LocalRotation = localRotation;
	const glm::vec3& LocalScale = localScale;
	
	void SetLocalPosition(glm::vec3 newPosition);
	void SetLocalRotation(glm::quat newRotation);
	void SetLocalScale(glm::vec3 newScale);
};
