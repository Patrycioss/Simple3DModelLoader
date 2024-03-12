
#include <cstdio>
#include <functional>

#include "ShaderProgram.hpp"
#include "Triangle.hpp"
#include "window/window.hpp"
#include "glad/gl.h"

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
	
	ShaderProgram triangle1Program({ShaderProgram::MakeShaderPath("vertex"), ShaderProgram::MakeShaderPath("fragment")});
	ShaderProgram triangle2Program({ShaderProgram::MakeShaderPath("vertex"), ShaderProgram::MakeShaderPath("fragment2")});

	while (!window->ShouldClose())
	{
		window->Preframe();
		printf("hahaha \n");
		
		glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(triangle1Program.GetID());
		triangle1.Draw();

		glUseProgram(triangle2Program.GetID());
		triangle2.Draw();

		window->Postframe();
	}

	glDeleteProgram(triangle1Program.GetID());
	glDeleteProgram(triangle2Program.GetID());
	
	window->Destroy();

	delete(window);
	return 0;
}