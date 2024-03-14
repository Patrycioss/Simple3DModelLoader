#include "GlfwWindow.hpp"

#include <cstdio>
#include <functional>
#include <stdexcept>

#include "../../rendering/ShaderProgram.hpp"
#include "../../KeyCode.hpp"

void GlfwWindow::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	float lastX = 400, lastY = 300;

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
}

void processInput(GLFWwindow* window)
{
	
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool GlfwWindow::InternalGetKey(const int glfwKey) const
{
	return glfwGetKey(window, glfwKey) == GLFW_PRESS;
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

void Init(std::function<void(void)> f);

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

class KeyCodeNotImplementedException final : public std::runtime_error
{
public:
	explicit KeyCodeNotImplementedException(const std::string& message) : runtime_error(message){}
};

bool GlfwWindow::GetKey(const KeyCode keyCode)
{
	switch(keyCode)
	{
		case KeyCode::W:
			return InternalGetKey(GLFW_KEY_W);
		case KeyCode::S:
			return InternalGetKey(GLFW_KEY_S);
		case KeyCode::A:
			return InternalGetKey(GLFW_KEY_A);
		case KeyCode::D:
			return InternalGetKey(GLFW_KEY_D);
		default:
			std::string message{};
			message.append("Key with value '");
			message.append(reinterpret_cast<char*>(keyCode));
			message.append("' not found!");
			throw KeyCodeNotImplementedException(message);
	}
}
