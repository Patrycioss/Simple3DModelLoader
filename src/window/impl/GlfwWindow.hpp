#pragma once

#include "../window.hpp"
#include "glad/gl.h"
#include "GLFW/glfw3.h"

class GlfwWindow : public Window
{
private:
	GLFWwindow* window = nullptr;
	const char* windowTitle = nullptr;

	bool InternalGetKey(int glfwKey) const;
	void MouseCallback(GLFWwindow* window, double xpos, double ypos);

public:
	explicit GlfwWindow(const Vec2<int>& size, const char* windowTitle);
	void Destroy() override;
	void Preframe() override;
	void Postframe() override;
	bool ShouldClose() override;
	bool GetKey(KeyCode keyCode) override;
};
