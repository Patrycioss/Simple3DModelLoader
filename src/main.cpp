
#include <cmath>
#include <cstdio>
#include <functional>

#include "Material.hpp"
#include "asyncoperations/ReadImageOperation.hpp"
#include "rendering/ShaderProgram.hpp"
#include "rendering/Triangle.hpp"
#include "window/window.hpp"
#include "glad/gl.h"
#include "rendering/Rectangle.hpp"

#define WINDOWTYPE 0

#if WINDOWTYPE == 0
	#include "window/impl/GlfwWindow.hpp"
#else
	#include "window/impl/Win32Window.hpp"
#endif

int main()
{
	Window* window;
	
#if WINDOWTYPE == 0
	constexpr Vec2 windowSize{800,600};
	constexpr auto windowTitle = "GLFW Window";
	window = new GlfwWindow(windowSize, windowTitle);

#else
	constexpr Vec2 windowSize{800,600};
	constexpr auto windowTitle = "Win32 Window";
	window = new Win32Window(windowSize, windowTitle);

#endif

	
	const Triangle triangle1{{-0.9f, -0.5f}, {-0.0f, -0.5f}, {-0.45f, 0.5f}};
	const Triangle triangle2{{0.0f, -0.5f}, {0.9f, -0.5f}, {0.45f, 0.5f}};
	const Rectangle rectangle{{-0.5f, 0.5f}, {-0.5f, -0.5f}, {0.5f, -0.5f}, {0.5f, 0.5f}};

	const ShaderProgram basicProgram({ShaderProgram::MakeShaderPath("vertex"), ShaderProgram::MakeShaderPath("fragment")});

	Material material(basicProgram, "resources/textures/awesomeface.png");
	
	while (!window->ShouldClose())
	{
		window->Preframe();
		printf("hahaha \n");
		
		glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT);

		material.Apply();		
		// triangle1.Draw();
		rectangle.Draw();

		// const auto timeValue = static_cast<float>(glfwGetTime());
		// const float greenValue = std::sin(timeValue) / 2.0f + 0.5f;
		// glUniform4f(colorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		// triangle2.Draw();
		// rectangle.Draw();

		window->Postframe();
	}

	window->Destroy();

	delete(window);
	return 0;
}