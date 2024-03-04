#include "Win32Window.hpp"

#include <iostream>
#include <string>

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
	printf("msg: 0x%04x \n", msg);
	
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

Win32Window::Win32Window(const std::function<void()>& renderFunction, const LPCSTR windowTitle)
	: windowTitle(windowTitle)
{
	this->renderFunction = renderFunction;
}

void Win32Window::Setup(const int width, const int height)
{
	printf("Setting up Windows Window!\n");

	printf("Defining Window.... \n");

	auto *const hInstance = HINST_THISCOMPONENT;
	
	window.cbSize = sizeof(WNDCLASSEX);
	window.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	// window.hCursor = LoadCursor(hInstance, IDC_ARROW);
	// window.hIcon   = LoadIcon(hInstance, IDI_APPLICATION);
	window.lpfnWndProc   = WndProc;
	window.hInstance = hInstance;
	window.lpszClassName = WINDOW_CLASS_NAME;
	window.style = CS_HREDRAW | CS_VREDRAW;
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
		width, height,
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
			renderFunction();
		}
	}

	printf("Closing \n");
}

void Win32Window::Destroy()
{
	printf("Destroying Window...\n");

	DestroyWindow(hwnd);
	HandleError("DestroyWindow");

	printf("Destroyed Window!\n");

	printf("Unregistering Window...\n");

	UnregisterClass(WINDOW_CLASS_NAME, HINST_THISCOMPONENT);
	HandleError("UnregisterClass");

	printf("Unregistered Window!\n");
}