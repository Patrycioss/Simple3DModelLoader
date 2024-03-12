#include "GlfwWindow.hpp"

#include <cstdio>

#include "../../rendering/ShaderProgram.hpp"

void processInput(GLFWwindow* window)
{
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GlfwWindow::GlfwWindow(const Vec2<int>& size, const char* windowTitle)
{
	this->size = size;
	this->windowTitle = windowTitle;

	printf("Setting up Window...\n");

	glfwInit();
	constexpr Vec2 GL_VERSION_NUMBER{4, 6};
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_NUMBER.X);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_NUMBER.Y);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	printf("Set up Window!\n");

	window = glfwCreateWindow(size.X, size.Y, windowTitle, nullptr, nullptr);

	if (window == nullptr)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	gladLoadGL(glfwGetProcAddress);
}

void GlfwWindow::Destroy()
{
	printf("Destroying GLFW Window...\n");

	glfwDestroyWindow(window);
	glfwTerminate();

	printf("Destroyed GLFW Window!\n");
}

void GlfwWindow::Preframe()
{
	processInput(window);
}

void GlfwWindow::Postframe()
{
	glfwPollEvents();
	glfwSwapBuffers(window);
}

bool GlfwWindow::ShouldClose()
{
	return glfwWindowShouldClose(window) != 0;
}