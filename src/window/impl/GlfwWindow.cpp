#include "GlfwWindow.hpp"

#include <cstdio>

#include "../../ShaderProgram.hpp"

auto vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

auto fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

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