
#include <cstdio>
#include <functional>

#include "FileReader.hpp"
#include "ShaderProgram.hpp"
#include "window/window.hpp"

#define WINDOWTYPE 0

#if WINDOWTYPE == 0
	#include "window/impl/GlfwWindow.hpp"
#else
	#include "window/impl/Win32Window.hpp"
#endif

int main()
{
	Window* window;

	auto renderFunction = []()
	{
		printf("hahaha \n");
		
		glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT);
	};
	
#if WINDOWTYPE == 0
	constexpr Vec2 windowSize{800,600};
	constexpr auto windowTitle = "GLFW Window";
	window = new GlfwWindow(windowSize, windowTitle, renderFunction);

#else
	constexpr Vec2 windowSize{800,600};
	constexpr auto windowTitle = "Win32 Window";
	window = new Win32Window(windowSize, windowTitle, renderFunction);

#endif

	window->Setup();
	window->Run();
	window->Destroy();


	return 0;
}