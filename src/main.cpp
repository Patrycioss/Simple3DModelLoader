#include <cmath>

#include "shaders/ShaderProgram.hpp"
#include "window/window.hpp"
#include <glad/gl.h>
#include "GLFW/glfw3.h"
#include "scene/Camera.hpp"
#include "scene/Scene.hpp"
#include "renderer/MeshRenderer.hpp"
#include "IO/ModelLoader.hpp"
#include "scene/GameObject.hpp"

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

	const float xOffset = (float) (mousePos.x - lastPos.x);
	const float yOffset = (float) (lastPos.y - mousePos.y); // reversed since y-coordinates go from bottom to top

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
	const float currentFrame = (float) glfwGetTime();
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

	Mesh* cubeMesh = ModelLoader::LoadModel("resources/models/cube/cube.obj");

	GameObject* parentObject = new GameObject("Parent");
	MeshRenderer* parentRenderer = new MeshRenderer();
	
	parentRenderer->AssignMesh(cubeMesh);

	parentObject->AssignRenderer(parentRenderer);
	scene.AddGameObject(parentObject);
	
	GameObject* childObject = new GameObject("Child");
	MeshRenderer* childRenderer = new MeshRenderer();
	childObject->AssignRenderer(childRenderer);
	childRenderer->AssignMesh(cubeMesh);
	childObject->SetParent(parentObject);
	childObject->Transform.SetLocalPosition(glm::vec3(0,4,0));

//	GameObject* childChildObject = new GameObject("Child");
//	MeshRenderer* childChildRenderer = new MeshRenderer();
//	childChildObject->AssignRenderer(childChildRenderer);
//	childChildRenderer->AssignMesh(cubeMesh);
//	childChildObject->SetParent(childObject);
//	childChildObject->Transform.SetLocalPosition(glm::vec3(0,8,0));
	
	Transform& parentTransform = parentObject->Transform;

	constexpr float PI = glm::pi<float>();
	constexpr float angle = PI/50.0f;
	constexpr glm::vec3 axis{0,0,1};
	
	while (!window.ShouldClose())
	{
		if (window.GetKey(GLFW_KEY_L) == GLFW_PRESS){
			auto r = parentTransform.LocalRotation * glm::angleAxis(angle, axis);
			parentTransform.SetLocalRotation(r);
//			childObject->Transform.SetLocalRotation(r);

			printf("LocalAngle: %f \n", glm::angle(parentTransform.LocalRotation) / glm::pi<float>());
		}
		
		CheckShouldCloseWindow(window);     
		LookAround(window, deltaTime, camera, lastPos, firstMouse);
		CalcDeltaTime(deltaTime, lastFrame);

		ClearScreen();

//		parentObject->Transform.SetPosition(parentObject->Transform.Position + glm::vec3{0.01f,0,0});
		
		scene.Draw();
		
		window.Postframe();
	}

	return 0;
}
