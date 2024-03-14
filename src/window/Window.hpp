#pragma once

#include "../data/Vec2.hpp"

enum class KeyCode;

class Window
{
public:
	
	
protected:
	Vec2<int> size;
	
public:
	virtual void Preframe() = 0;
	virtual void Postframe() = 0;
	virtual void Destroy() = 0;
	virtual bool ShouldClose() = 0;

	Vec2<int> Size();

	virtual bool GetKey(KeyCode keyCode) = 0;
};
