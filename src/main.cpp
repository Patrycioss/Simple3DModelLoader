
#include <cmath>
#include <functional>

#include "Material.hpp"
#include "rendering/ShaderProgram.hpp"
#include "window/window.hpp"
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "rendering/GLCube.hpp"
#include "rendering/GLRectangle.hpp"
#include "rendering/GLTriangle.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
	Window window{{800,600}, "GLFW Window"};

	glEnable(GL_DEPTH_TEST);
	
	const GLShapes::GLTriangle triangle1{
		{-0.9f, -0.5f},
		{-0.0f, -0.5f},
		{-0.45f, 0.5f}
	};
	
	const GLShapes::GLTriangle triangle2{
		{0.0f, -0.5f},
		{0.9f, -0.5f},
		{0.45f, 0.5f}
	};
	
	const GLShapes::GLRectangle rectangle{};

	const GLShapes::GLCube cube{};

	const ShaderProgram basic2DProgram("resources/shaders/vertex2D.glsl",
									 "resources/shaders/fragment2D.glsl");
	const ShaderProgram basic3DProgram("resources/shaders/vertex3D.glsl",
	                                 "resources/shaders/fragment3D.glsl");

	const Texture texture("resources/textures/awesomeface.png");
	const Material basic3Dmaterial(basic3DProgram, texture);
	const Material basic2Dmaterial(basic2DProgram, texture);

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);  
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = normalize(cameraPos - cameraTarget);
	
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
	glm::vec3 cameraRight = normalize(cross(up, cameraDirection));
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = cross(cameraDirection, cameraRight);

	glm::mat4 view = glm::mat4(1.0f);

	constexpr int cubeAmount = 10;

	constexpr glm::vec3 cubePositions[cubeAmount] = {
		glm::vec3( 0.0f,  0.0f,  0.0f), 
		glm::vec3( 2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f)  
	};

	
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	
	while (!window.ShouldClose())
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;  
		
		window.Preframe();

		float cameraSpeed = 10 * deltaTime;
		if (window.GetKey(GLFW_KEY_W))
		{
			cameraPos += cameraSpeed * cameraFront;
		}
		if (window.GetKey(GLFW_KEY_S))
		{
			cameraPos -= cameraSpeed * cameraFront;
		}
		if (window.GetKey(GLFW_KEY_A))
		{
			cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		if (window.GetKey(GLFW_KEY_D))
		{
			cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		
		glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		basic3Dmaterial.Apply();

		glm::abs(5);
		
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		const unsigned int viewLoc = basic3DProgram.GetUniformLocation("view");
		const unsigned int projectionLoc = basic3DProgram.GetUniformLocation("projection");
		
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));
		
		for(unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model2 = glm::mat4(1.0f);
			model2 = translate(model2, cubePositions[i]);
			float angle = 20.0f * i; 
			model2 = rotate(model2, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			const unsigned int modelLoc = basic3Dmaterial.Shader().GetUniformLocation("model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model2));

			cube.Draw();
		}

		window.Postframe();
	}

	return 0;
}
