#include "GlfwWindow.hpp"

#include <cstdio>

void processInput(GLFWwindow* window)
{
	
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}  

GlfwWindow::GlfwWindow(const Vec2<int>& size, const char* windowTitle, const std::function<void()>& renderFunction)
{
	this->size = size;
	this->windowTitle = windowTitle;
	this->renderFunction = renderFunction;
}

void GlfwWindow::Setup()
{
	printf("Setting up Window...\n");

	glfwInit();
	constexpr Vec2 GL_VERSION_NUMBER{4,3};
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_NUMBER.X);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_NUMBER.Y);
	
	// glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	printf("Set up Window!\n");
}

void GlfwWindow::Run()
{
	window = glfwCreateWindow(size.X, size.Y, windowTitle, nullptr, nullptr);

	if (window == nullptr)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
	
	while (glfwWindowShouldClose(window) == 0)
	{
		// Input
		processInput(window);
		
		renderFunction();
		
		// Call events, swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	
	glfwPollEvents();
}

void GlfwWindow::Destroy()
{
	printf("Destroying GLFW Window...\n");

	glfwDestroyWindow(window);
	glfwTerminate();

	printf("Destroyed GLFW Window!\n");
}