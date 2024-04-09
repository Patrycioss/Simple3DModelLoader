#pragma once

namespace GLShapes {

class GLCube 
{
private:
	unsigned int VBO{};
	unsigned int VAO{};
	unsigned int EBO{};

public:
	explicit GLCube();
	void Draw() const;
	~GLCube();
};

}
