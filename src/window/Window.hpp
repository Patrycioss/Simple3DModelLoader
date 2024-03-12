#pragma once

#include "../data/Vec2.hpp"

class Window
{
protected:
	Vec2<int> size;
	
public:
	virtual void Preframe() = 0;
	virtual void Postframe() = 0;
	virtual void Destroy() = 0;
	virtual bool ShouldClose() = 0;

	Vec2<int> Size();
};