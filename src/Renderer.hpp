#pragma once

#include <glm/fwd.hpp>
#include "Component.hpp"
#include "ShaderProgram.hpp"
#include "ResourceRepo.hpp"

class Renderer : public Component
{
protected:
	ShaderProgram shader{ResourceRepo::VertexShader(), ResourceRepo::FragmentShader()};
	
public:
	virtual void Render(const glm::mat4& mvpMatrix) = 0;
};
