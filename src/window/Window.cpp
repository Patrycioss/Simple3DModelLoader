#include "Window.hpp"

#include <cstdio>
#include <functional>

#include "../rendering/ShaderProgram.hpp"

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}

bool Window::InternalGetKey(const int glfwKey) const
{
	return glfwGetKey(window, glfwKey) == GLFW_PRESS;
}

void Window::MouseCallbacK(GLFWwindow* window, double xpos, double ypos) const
{
	printf("Member!");
}

Window::Window(const glm::vec2 size, const char* windowTitle)
{
	this->size = size;
	this->windowTitle = windowTitle;

	printf("Setting up Window...\n");

	glfwInit();
	constexpr glm::vec2 GL_VERSION_NUMBER{4, 6};
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_NUMBER.x);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_NUMBER.y);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	printf("Set up Window!\n");

	window = glfwCreateWindow(size.x, size.y, windowTitle, nullptr, nullptr);

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
		static_cast<Window*>(glfwGetWindowUserPointer(w))->MouseCallbacK(w, x, y);
	};
	
	glfwSetCursorPosCallback(window, func);
}

void Window::Postframe() const
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

Window::~Window()
{
	printf("Destroying GLFW Window...\n");

	glfwDestroyWindow(window);
	glfwTerminate();

	printf("Destroyed GLFW Window!\n");
}