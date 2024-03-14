#pragma once

#include <glm/vec2.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* window = nullptr;
	const char* windowTitle = nullptr;

	glm::vec2 size;
	
	bool InternalGetKey(int glfwKey) const;

public:
	explicit Window(glm::vec2 size, const char* windowTitle);
	void Destroy() const;
	void Preframe() const;
	void Postframe() const;
	bool ShouldClose() const;
	bool GetKey(int glfwKey, int glfwKeyState = GLFW_PRESS) const;
	~Window();
};
