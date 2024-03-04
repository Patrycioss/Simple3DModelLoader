#pragma once

#include "../window.hpp"
#include "GLFW/glfw3.h"

class GlfwImpl : public Window
{
private:
	GLFWwindow* window = nullptr;

public:
	void Setup(int width, int height) override;
	void Run() override;
	void Destroy() override;
};
