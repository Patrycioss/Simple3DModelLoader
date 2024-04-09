#pragma once

namespace GLShapes
{
	class GLRectangle
	{
	private:
		unsigned int VBO{};
		unsigned int VAO{};
		unsigned int EBO{};

	public:
		explicit GLRectangle();
		void Draw() const;
		~GLRectangle();
	};
}
