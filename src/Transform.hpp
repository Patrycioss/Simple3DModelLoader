#pragma once


#include <glm/vec3.hpp>
#include<glm/gtc/quaternion.hpp>

class Transform
{
public:
	glm::vec3 position = glm::vec3(0);
	glm::quat rotation = glm::mat4(1.0f);
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	
	Transform operator=(Transform transform) = delete;
};
