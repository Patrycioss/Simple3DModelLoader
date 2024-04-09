#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float SPEED = 2.5f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM = 45.0f;

class Camera
{
public:
	struct SpatialInformation{
		glm::vec3 position;
		glm::vec3 up;
		float yaw;
		float pitch;
	};
	
	struct ProjectionSettings{
		float verticalFovDeg = 45.0f;
		float aspectRatio = 4.0f/3.0f;
		float nearClippingPlane = 0.1f;
		float farClippingPlane = 100.0f;
	};
	
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;


	glm::mat4 projectionMatrix;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	explicit Camera(
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			float yaw = YAW, float pitch = PITCH
	);

	glm::mat4 GetProjectionMatrix() const;
	glm::mat4 GetViewMatrix() const;

	void ProcessKeyboard(const Camera_Movement direction, const float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, const bool constrainPitch = true);
	void ProcessMouseScroll(const float yoffset);

private:
	void UpdateCameraVectors();
};
