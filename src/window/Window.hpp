#pragma once

#include <functional>

class Window
{
protected:
	std::function<void()> renderFunction;
	
public:
	virtual void Setup(int width, int height) = 0;
	virtual void Run() = 0;
	virtual void Destroy() = 0;
};
