#pragma once

#include "../window.hpp"

#define WIN32_LEAN_AND_MEAN
#include <glad/gl.h>
#include <Windows.h>

class Win32Window final : public Window
{
private:
	WNDCLASSEX window{};
	HWND hwnd{};
	LPCSTR windowTitle;
	const LPCSTR WINDOW_CLASS_NAME = "MyWindow";
	bool shouldClose = false;

	HDC__* deviceContext = nullptr;

	LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	explicit Win32Window(const Vec2<int>& size, const LPCSTR& windowTitle);
	void Destroy() override;
	void Preframe() override;
	void Postframe() override;
	bool ShouldClose() override;
};