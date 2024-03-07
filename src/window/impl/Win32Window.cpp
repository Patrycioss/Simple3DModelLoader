#include "Win32Window.hpp"

#include <iostream>
#include <string>
#include <_bsd_types.h>
#include <glad/gl.h>
#include "../../ShaderProgram.hpp"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

class WindowException final : public std::runtime_error
{
private:
	std::string message;

public:
	explicit WindowException(const std::string& message) : runtime_error(message)
	{
		this->message = message;
	}
	
	[[nodiscard]] const char* what() const noexcept override
	{
		return message.c_str();
	}
};

std::string GetLastErrorAsString()
{
	const DWORD err = GetLastError();

	if (!err) { return ""; }

	char* message = nullptr;

	const size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
	                                   nullptr,
	                                   err,
	                                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	                                   reinterpret_cast<char*>(&message), 0, nullptr);

	std::string rez(message,size);
	LocalFree(message);
	return rez;
}

void HandleError(const char* operation, const bool failure = false)
{
	const std::string foundError = GetLastErrorAsString();
	std::string error;

	if (!foundError.empty())
	{
		error += "Window operation: '";
		error.append(operation);
		error.append("' failed with error: '");
		error.append(foundError + "'");
		throw WindowException(error);
	}

	if (failure)
	{
		error.append("Window operation: '");
		error.append(operation);
		error.append("' failed without errors!");
		throw WindowException(error);
	}
}

LRESULT Win32Window::windowProcedure(const HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
{
	// printf("msg: 0x%04x \n", msg);
	
	switch (msg)
	{
		case WM_CLOSE:
		{
			shouldClose = true;
			break;
		}
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

LRESULT Win32Window::WndProc(HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
{
	if (auto *const windowsImpl = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)))
	// if (const auto windowsImpl = reinterpret_cast<WindowsImpl*>(lParam))
	{
		return windowsImpl->windowProcedure(hwnd, msg, wParam, lParam);
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

Win32Window::Win32Window(const Vec2<int>& size, const LPCSTR& windowTitle, const std::function<void()>& renderFunction)
	: windowTitle(windowTitle)
{
	this->size = size;
	this->windowTitle = windowTitle;
	this->renderFunction = renderFunction;
}

void Win32Window::Setup()
{
	printf("Setting up Windows Window!\n");

	printf("Defining Window.... \n");

	auto *const hInstance = HINST_THISCOMPONENT;
	
	window.cbSize = sizeof(WNDCLASSEX);
	// window.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	// window.hCursor = LoadCursor(hInstance, IDC_ARROW);
	// window.hIcon   = LoadIcon(hInstance, IDI_APPLICATION);
	window.lpfnWndProc   = WndProc;
	window.hInstance = hInstance;
	window.lpszClassName = WINDOW_CLASS_NAME;
	window.style = CS_OWNDC;
	window.cbWndExtra = 0;
	window.cbClsExtra = 0;
	window.lpszMenuName = nullptr;
	
	RegisterClassEx(&window);
	HandleError("RegisterWindow");

	printf("Defined Window! \n");
	
	printf("Creating Window... \n");

	hwnd = CreateWindowExA(
		0,							  //style stuff
		WINDOW_CLASS_NAME,                   //The actual window name to find it with
		windowTitle,                   //Window Title
		WS_OVERLAPPEDWINDOW,          //style stuff
		CW_USEDEFAULT, CW_USEDEFAULT, //position x,y
		size.X, size.Y,
		nullptr,
		nullptr,
		window.hInstance,
		this
	);

	HandleError("CreateWindow");

	SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	printf("Created Window! \n");
}

void Win32Window::Run()
{
	printf("Creating OpenGL context...\n");
	//OpenGL Setup
	constexpr PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	auto *const deviceContext = GetDC(hwnd);

	const auto pixelFormatNumber = ChoosePixelFormat(deviceContext, &pfd);
	
	SetPixelFormat(deviceContext, pixelFormatNumber, &pfd);
	auto *const glContext = wglCreateContext(GetDC(hwnd));
	wglMakeCurrent(deviceContext, glContext);
	
	gladLoaderLoadGL();
	
	printf("Created OpenGL context!\n");

	constexpr float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	ShaderProgram shaderProgram({ShaderProgram::MakeShaderPath("vertex"), ShaderProgram::MakeShaderPath("fragment")});
	
	glLinkProgram(shaderProgram.GetID());
	
	MSG msg;

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	while (!shouldClose)
	{
		if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		else
		{
			glUseProgram(shaderProgram.GetID());
			glBindVertexArray(VAO);
			renderFunction();
			glDrawArrays(GL_TRIANGLES, 0, 3);

			SwapBuffers(deviceContext);
		}
	}

	printf("Closing \n");
}

void Win32Window::Destroy()
{
	printf("Destroying Window...\n");

	printf("Unregistering OpenGL context...\n");
	wglDeleteContext(wglGetCurrentContext());
	printf("Unregistered OpenGL context!\n");

	
	DestroyWindow(hwnd);
	HandleError("DestroyWindow");

	printf("Destroyed Window!\n");

	printf("Unregistering Window...\n");

	UnregisterClass(WINDOW_CLASS_NAME, HINST_THISCOMPONENT);
	HandleError("UnregisterClass");

	printf("Unregistered Window!\n");
}