#include <cmath>

#include "ShaderProgram.hpp"
#include "window/window.hpp"
#include <glad/gl.h>
#include "GLFW/glfw3.h"
#include "Camera.hpp"
#include "Scene.hpp"
#include "MeshRenderer.hpp"
#include "GameObject.hpp"
#include "ModelLoader.hpp"

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

	const float xOffset = mousePos.x - lastPos.x;
	const float yOffset = lastPos.y - mousePos.y; // reversed since y-coordinates go from bottom to top

	lastPos = mousePos;

	camera.ProcessMouseMovement(xOffset, yOffset);

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

void PrintVec2(const glm::vec2& v)
{
	printf("{%f,%f}\n", v.x, v.y);
}

void PrintVec3(const glm::vec3& v)
{
	printf("{%f,%f,%f}\n", v.x, v.y, v.z);
}

int main()
{
	float deltaTime = 0.0f; // Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
	
	// ------- OpenGL Settings / Window Creation / Camera ----------- //
	Window window{{1980, 1200}, "GLFW Window"};
	window.SetMouseFocus(Window::CursorMode::Normal);

	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it is closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	glm::vec2 lastPos = window.Size() / 2.0f;
	bool firstMouse = true;
	
	Scene scene(camera);

	GameObject* gameObject = new GameObject();
	
	MeshRenderer* meshRenderer = new MeshRenderer();
	
	NewMesh* mesh = ModelLoader::LoadModel("resources/models/backpack/backpack.obj");
	meshRenderer->AssignMesh(mesh);
	meshRenderer->Setup();

	gameObject->AssignRenderer(meshRenderer);
	scene.AddGameObject(gameObject);
	
	while (!window.ShouldClose())
	{
		CheckShouldCloseWindow(window);     
		LookAround(window, deltaTime, camera, lastPos, firstMouse);
		CalcDeltaTime(deltaTime, lastFrame);

		ClearScreen();

		scene.Draw();
		
		
		window.Postframe();
	}

	return 0;
}
