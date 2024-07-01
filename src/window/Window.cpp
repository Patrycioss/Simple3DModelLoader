#include "Window.hpp"

#include <cstdio>
#include <functional>

#include "../shaders/ShaderProgram.hpp"

constexpr float mouseSensitivity = 0.1f;

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}

bool Window::InternalGetKey(const int glfwKey) const
{
	return glfwGetKey(window, glfwKey) == GLFW_PRESS;
}

void Window::MouseCallback(GLFWwindow* window, double xPos, double yPos) const
{
	mousePos = {xPos, yPos};
}

const glm::dvec2& Window::MousePos() const
{
	return mousePos;
}

Window::Window(const glm::vec2 size, const char* windowTitle)
{
	this->size = size;
	this->windowTitle = windowTitle;
	this->mousePos = {size.x/2, size.y/2};

	printf("Setting up Window...\n");

	glfwInit();
	constexpr glm::vec2 GL_VERSION_NUMBER{4, 6};
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_NUMBER.x);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_NUMBER.y);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_AUTO_ICONIFY, false);

	
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
 
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	printf("Set up Window!\n");

    window = glfwCreateWindow(mode->width, mode->height, "My Title", nullptr, nullptr);
	
	if (window == nullptr)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	gladLoadGL(glfwGetProcAddress);

	glfwSetWindowUserPointer(window, this);
	
	auto func = [](GLFWwindow* w, const double x, const double y)
	{
		static_cast<Window*>(glfwGetWindowUserPointer(w))->MouseCallback(w, x, y);
	};
	
	glfwSetCursorPosCallback(window, func);
}

void Window::PostFrame() const
{
	glfwPollEvents();
	glfwSwapBuffers(window);
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(window) != 0;
}

bool Window::GetKey(const int glfwKey, const int glfwKeyState) const
{
	return glfwGetKey(window, glfwKey) == glfwKeyState;
}

glm::vec2 Window::Size() const
{
	return size;
}

void Window::Close() const
{
	glfwSetWindowShouldClose(window, true);
}

void Window::SetMouseFocus(const CursorMode cursorMode) const
{
	int mode;

	switch (cursorMode)
	{
		case CursorMode::Captured:
			mode = GLFW_CURSOR_CAPTURED;
			break;
		case CursorMode::Disabled:
			mode = GLFW_CURSOR_DISABLED;
			break;
		case CursorMode::Hidden:
			mode = GLFW_CURSOR_HIDDEN;
		break;

		case CursorMode::Normal:
		default:
			mode = GLFW_CURSOR_NORMAL;
		break;
	}
	
	glfwSetInputMode(window, GLFW_CURSOR, mode);
}

Window::~Window()
{
	printf("Destroying GLFW Window...\n");

	glfwDestroyWindow(window);
	glfwTerminate();

	printf("Destroyed GLFW Window!\n");
}
