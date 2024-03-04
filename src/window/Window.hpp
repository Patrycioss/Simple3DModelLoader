#pragma once

#include <functional>
#include "../data/Vec2.hpp"

class Window
{
protected:
	std::function<void()> renderFunction;
	Vec2<int> size;
	
public:
	virtual void Setup() = 0;
	virtual void Run() = 0;
	virtual void Destroy() = 0;

	Vec2<int> Size();
};
