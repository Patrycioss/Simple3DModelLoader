#pragma once

#include <glm/vec2.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	enum class CursorMode
	{
		Normal,
		Captured,
		Hidden,
		Disabled
	};
	
private:
	GLFWwindow* window = nullptr;
	const char* windowTitle = nullptr;

	glm::vec2 size;
	mutable glm::dvec2 mousePos;
	
	bool InternalGetKey(int glfwKey) const;
	void MouseCallbacK(GLFWwindow* window, double xpos, double ypos) const;

public:
	const glm::dvec2& MousePos() const;
	explicit Window(glm::vec2 size, const char* windowTitle);
	void Postframe() const;
	bool ShouldClose() const;
	bool GetKey(int glfwKey, int glfwKeyState = GLFW_PRESS) const;
	glm::vec2 Size() const;
	void Close() const;
	void SetMouseFocus(CursorMode cursorMode) const;
	~Window();
};
