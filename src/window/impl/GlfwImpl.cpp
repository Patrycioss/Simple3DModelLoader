#include "GlfwImpl.hpp"

#include <cstdio>

void GlfwImpl::Setup(const int width, const int height)
{
	printf("Setting up GLFW Window!");

	glfwInit();
	
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(width, height, "Vulkan window", nullptr, nullptr);
}

void GlfwImpl::Run()
{
	glfwPollEvents();
}

void GlfwImpl::Destroy()
{
	printf("Destroying GLFW Window!");

	glfwDestroyWindow(window);
	glfwTerminate();
}