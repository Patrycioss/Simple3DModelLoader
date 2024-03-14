#pragma once

#include "../data/Vec2.hpp"

namespace Shapes
{
	class Rectangle
	{
	private:
		unsigned int VBO{};
		unsigned int VAO{};
		unsigned int EBO{};

	public:
		explicit Rectangle(Vec2<float> topLeft, Vec2<float> bottomLeft, Vec2<float> bottomRight, Vec2<float> topRight);
		void Draw() const;
		~Rectangle();
	};
}
