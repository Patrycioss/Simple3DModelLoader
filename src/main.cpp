#include <cmath>
#include <functional>

#include "Material.hpp"
#include "rendering/ShaderProgram.hpp"
#include "rendering/Triangle.hpp"
#include "window/window.hpp"
#include "glad/gl.h"
#include "rendering/Rectangle.hpp"

#define WINDOWTYPE 1

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
	constexpr Vec2 windowSize{800, 600};
	constexpr auto windowTitle = "Win32 Window";
	window = new Win32Window(windowSize, windowTitle);

#endif

	const Shapes::Triangle triangle1{{-0.9f, -0.5f}, {-0.0f, -0.5f}, {-0.45f, 0.5f}};
	const Shapes::Triangle triangle2{{0.0f, -0.5f}, {0.9f, -0.5f}, {0.45f, 0.5f}};
	const Shapes::Rectangle rectangle{{-0.5f, 0.5f}, {-0.5f, -0.5f}, {0.5f, -0.5f}, {0.5f, 0.5f}};

	const ShaderProgram basicProgram("resources/shaders/vertex.glsl",
	                                 "resources/shaders/fragment.glsl");

	const Texture texture("resources/textures/awesomeface.png");
	const Material material(basicProgram, texture);

	while (!window->ShouldClose())
	{
		window->Preframe();

		glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT);

		material.Apply();
		rectangle.Draw();

		window->Postframe();
	}

	window->Destroy();

	delete(window);
	return 0;
}
