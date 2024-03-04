#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "window/window.hpp"

#include <iostream>
#include <functional>

#include "window/impl/GlfwImpl.hpp"
#include "window/impl/Win32Window.hpp"

void TestStuff()
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::cout << extensionCount << " extensions supported\n";

	glm::mat4 matrix = glm::mat4{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};
	glm::vec4 vec = glm::vec4{5,5,5,5};
	const auto test = matrix * vec;
	printf("%f", test.x);
}

void Update()
{
	printf("Updating...\n");
}

int main()
{
	glewInit();
	
	Window* window = new Win32Window(Update);
	
	window->Setup(800, 600);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	}; 

	
	unsigned int VBO;
	glGenBuffers(1, &VBO);  

	// TestStuff();
	window->Run();
	window->Destroy();

	return 0;
}
