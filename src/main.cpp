
#include <cmath>
#include <iostream>
#include <vector>

#include "rendering/structures/Material.hpp"
#include "rendering/ShaderProgram.hpp"
#include "window/window.hpp"
#include <glad/gl.h>
#include "GLFW/glfw3.h"
#include "rendering/GLCube.hpp"
#include "rendering/GLRectangle.hpp"
#include "rendering/GLTriangle.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vulkan/vulkan.h>

#include <rapidobj/rapidobj.hpp>
#include <dds.hpp>


#include "Camera.hpp"
#include "FakeObjects.hpp"
#include "obj-loading/LoadFastObjMeshOperation.hpp"
#include "rendering/structures/Mesh.hpp"

void CheckShouldCloseWindow(const Window& window)
{
	if (window.GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
		window.Close();
}

void LookAround(const Window& window, const float& deltaTime, Camera& camera, glm::vec2& lastPos, bool& firstMouse)
{
	const glm::dvec2 mousePos = window.MousePos();

	if (firstMouse)
	{
		lastPos = mousePos;
		firstMouse = false;
	}

	const float xoffset = mousePos.x - lastPos.x;
	const float yoffset = lastPos.y - mousePos.y; // reversed since y-coordinates go from bottom to top

	lastPos = mousePos;

	camera.ProcessMouseMovement(xoffset, yoffset);
		
		

	if (window.GetKey(GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (window.GetKey(GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (window.GetKey(GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (window.GetKey(GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void CalcDeltaTime(float& deltaTime, float& lastFrame)
{
	const float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void ClearScreen()
{
	glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DrawCubes(const GLShapes::GLCube& cube, const Material& basic3Dmaterial, const glm::vec3 cubePositions[10])
{
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
}

void PrintVec2(const glm::vec2& v)
{
	printf("{%f,%f}\n", v.x, v.y);
}

void PrintVec3(const glm::vec3& v)
{
	printf("{%f,%f,%f}\n", v.x, v.y,v.z);
}

int main()
{
	constexpr float VERTICAL_FOV = glm::radians(45.0f); 
	constexpr float ASPECT_RATIO = 4.0f/3.0f;
	constexpr float NEAR_CLIPPING_PLANE = 0.1f;
	constexpr float FAR_CLIPPING_PLANE = 100.0f;

	const glm::mat4 projectionMatrix = glm::perspective(
		VERTICAL_FOV,
		ASPECT_RATIO,
		NEAR_CLIPPING_PLANE,
		FAR_CLIPPING_PLANE
	);
	
	Window window{{1980,1200}, "GLFW Window"};

	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it is closer to the camera than the former one
	glDepthFunc(GL_LESS);
	
	// Cull triangles which normal is not towards the camera
	// ENABLE THIS WHEN PROPER OBJ LOADING UNTIL THEN IGNORE :D
	// glEnable(GL_CULL_FACE);

	const ShaderProgram basicModelProgram("resources/shaders/vertexModel.glsl",
									 "resources/shaders/fragmentModel.glsl");

	const Texture texture("resources/textures/awesomeface.png");
	const Material material(basicModelProgram, texture);

	
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	glm::vec2 lastPos = window.Size() / 2.0f;
	bool firstMouse = true;

	window.SetMouseFocus(Window::CursorMode::Hidden);

	Mesh mesh = Mesh(FakeObjects::cube);
	GLShapes::GLCube cube = GLShapes::GLCube();

	while (!window.ShouldClose())
	{
		CheckShouldCloseWindow(window);	
		LookAround(window, deltaTime, camera, lastPos, firstMouse);
		CalcDeltaTime(deltaTime, lastFrame);

		ClearScreen();
	

		glm::mat4 viewMatrix = camera.GetViewMatrix();
		glm::mat4 modelMatrix = glm::mat4(1.0);
		glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
		
		glUniformMatrix4fv(basicModelProgram.GetUniformLocation("MVP"), 1, GL_FALSE, &mvp[0][0]);

		basicModelProgram.Use();
		mesh.Draw();
		// cube.Draw();

		GLenum err;
		while((err = glGetError()) != GL_NO_ERROR)
		{
			printf("Error!!!!: %u", err);
		}
		
		window.Postframe();
	}

	// glDeleteTextures(1, &textureID);

	return 0;
}
