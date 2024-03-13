
#include <cmath>
#include <cstdio>
#include <functional>

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

	constexpr float texCoords[] = {
		0.0f, 0.0f, // bl
		1.0f, 0.0f, // br
		0.5f, 1.0f  // tc
	};

	unsigned int texture1, texture2;

	{
		ReadImageOperation wallOperation("resources/textures/container.jpg");
		ReadImageOperation awesomeOperation("resources/textures/awesomeface.png");

		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Nearest give hard pixel edges, linear mixes pixel colors based on neighbours so blurs
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Mipmapping only applies to MIN because it's used for smaller objects not bigger
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		const ReadImageOperation::ImageInfo wallInfo = wallOperation.AwaitResult();
		if (wallInfo.Data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wallInfo.Width, wallInfo.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, wallInfo.Data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		wallOperation.Free();

		glGenTextures(1, &texture2);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Nearest give hard pixel edges, linear mixes pixel colors based on neighbours so blurs
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Mipmapping only applies to MIN because it's used for smaller objects not bigger
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		const ReadImageOperation::ImageInfo awesomeInfo = awesomeOperation.AwaitResult();
		if (awesomeInfo.Data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, awesomeInfo.Width, awesomeInfo.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, awesomeInfo.Data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		awesomeOperation.Free();
	}

	basicProgram.Use();
	glUniform1i(basicProgram.GetUniformLocation("texture1"), 0);
	glUniform1i(basicProgram.GetUniformLocation("texture2"), 1);
	
	while (!window->ShouldClose())
	{
		window->Preframe();
		printf("hahaha \n");
		
		glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT);

		basicProgram.Use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		// triangle1.Draw();

		// const auto timeValue = static_cast<float>(glfwGetTime());
		// const float greenValue = std::sin(timeValue) / 2.0f + 0.5f;
		// glUniform4f(colorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		// triangle2.Draw();
		rectangle.Draw();

		window->Postframe();
	}

	window->Destroy();

	delete(window);
	return 0;
}