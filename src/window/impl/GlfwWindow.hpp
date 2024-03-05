#pragma once

#include "../window.hpp"
#include <glad/gl.h>
#include "GLFW/glfw3.h"

class GlfwWindow : public Window
{
private:
	GLFWwindow* window = nullptr;
	const char* windowTitle = nullptr;

public:
	explicit GlfwWindow(const Vec2<int>& size, const char* windowTitle, const std::function<void()>& renderFunction);
	void Setup() override;
	void Run() override;
	void Destroy() override;
};
