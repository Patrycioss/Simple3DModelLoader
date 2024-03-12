#pragma once
#include "data/Vec2.hpp"


class Triangle 
{
private:
	unsigned int VBO{};
	unsigned int VAO{};

public:
	explicit Triangle(Vec2<float> left, Vec2<float> right, Vec2<float> top);
	void Draw() const;
	~Triangle();
};
