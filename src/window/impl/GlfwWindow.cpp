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
	constexpr Vec2 GL_VERSION_NUMBER{4,6};
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_NUMBER.X);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_NUMBER.Y);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
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
	gladLoadGL(glfwGetProcAddress);

	
	constexpr float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
	   -0.5f, -0.5f, 0.0f,  // bottom left
	   -0.5f,  0.5f, 0.0f   // top left 
   };

	constexpr unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	constexpr float firstTriangle[] = {
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
	};
	
	constexpr float secondTriangle[] = {
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top 
	};

	unsigned int VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	// Triangle 1
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// Triangle 2
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	

	// unsigned int EBO;
	// glGenBuffers(1, &EBO);
	
	unsigned int VBO;
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	ShaderProgram triangle1Program({ShaderProgram::MakeShaderPath("vertex"), ShaderProgram::MakeShaderPath("fragment")});
	ShaderProgram triangle2Program({ShaderProgram::MakeShaderPath("vertex"), ShaderProgram::MakeShaderPath("fragment2")});
	
	while (glfwWindowShouldClose(window) == 0)
	{
		// Input
		processInput(window);

		glUseProgram(triangle1Program.GetID());

		renderFunction();
		// draw first triangle using the data from the first VAO
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		// then we draw the second triangle using the data from the second VAO
		glUseProgram(triangle2Program.GetID());
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		// Call events, swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(triangle1Program.GetID());
	glDeleteProgram(triangle2Program.GetID());
}

void GlfwWindow::Destroy()
{
	printf("Destroying GLFW Window...\n");

	glfwDestroyWindow(window);
	glfwTerminate();

	printf("Destroyed GLFW Window!\n");
}