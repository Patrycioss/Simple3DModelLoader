
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
#include "obj-loading/LoadFastObjMeshOperation.hpp"

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
	glEnable(GL_CULL_FACE);
	
	// const GLShapes::GLTriangle triangle1{
	// 	{-0.9f, -0.5f},
	// 	{-0.0f, -0.5f},
	// 	{-0.45f, 0.5f}
	// };
	//
	// const GLShapes::GLTriangle triangle2{
	// 	{0.0f, -0.5f},
	// 	{0.9f, -0.5f},
	// 	{0.45f, 0.5f}
	// };
	//
	//
	// const GLShapes::GLRectangle rectangle{};
	//
	// const GLShapes::GLCube cube{};

	// const ShaderProgram basic2DProgram("resources/shaders/vertex2D.glsl",
	// 								 "resources/shaders/fragment2D.glsl");
	// const ShaderProgram basic3DProgram("resources/shaders/vertex3D.glsl",
	//                                  "resources/shaders/fragment3D.glsl");

	const ShaderProgram basicModelProgram("resources/shaders/vertexModel.glsl",
									 "resources/shaders/fragmentModel.glsl");

	const Texture texture("resources/textures/awesomeface.png");
	// const Material basic3Dmaterial(basic3DProgram, texture);
	// const Material basic2Dmaterial(basic2DProgram, texture);
	// const Material basicModelMaterial(basicModelProgram, texture);

	dds::Image image;
	if (dds::readFile("resources/textures/uvmap.dds", &image) == dds::Failure)
	{
		throw "Failed to load uvmap.dds!";
	};

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, image.numMips-1); // opengl likes array length of mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // don't forget to enable mipmaping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	unsigned int offset = 0;
	unsigned int size = 0;

	unsigned int blockSize = (image.format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	
	for (unsigned int i=0; i<image.numMips; i++) {
		size = ((image.width+3)/4) * ((image.height+3)/4) * blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, i, image.format, image.width, image.height, 0, size, (image.data.data() + offset));
		offset += size;
		image.width /= 2;
		image.height /= 2;
	}
	// discard any odd mipmaps, ensure a complete texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, image.numMips-1);
	// unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	rapidobj::MaterialLibrary mtllib = rapidobj::MaterialLibrary::SearchPath("resources/materials", rapidobj::Load::Optional);
	rapidobj::Result result = rapidobj::ParseFile("resources/models/cube.obj", mtllib);
	
	//
	// constexpr int cubeAmount = 10;
	//
	// constexpr glm::vec3 cubePositions[cubeAmount] = {
	// 	glm::vec3( 0.0f,  0.0f,  0.0f), 
	// 	glm::vec3( 2.0f,  5.0f, -15.0f), 
	// 	glm::vec3(-1.5f, -2.2f, -2.5f),  
	// 	glm::vec3(-3.8f, -2.0f, -12.3f),  
	// 	glm::vec3( 2.4f, -0.4f, -3.5f),  
	// 	glm::vec3(-1.7f,  3.0f, -7.5f),  
	// 	glm::vec3( 1.3f, -2.0f, -2.5f),  
	// 	glm::vec3( 1.5f,  2.0f, -2.5f), 
	// 	glm::vec3( 1.5f,  0.2f, -1.5f), 
	// 	glm::vec3(-1.3f,  1.0f, -1.5f)  
	// };

	
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	glm::vec2 lastPos = window.Size() / 2.0f;
	bool firstMouse = true;

	window.SetMouseFocus(Window::CursorMode::Hidden);
	
	std::vector<glm::vec3> vertices{};
	std::vector<glm::vec2> uvs{};
	std::vector<glm::vec3> normals{};

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	while (!window.ShouldClose())
	{
		CheckShouldCloseWindow(window);	
		LookAround(window, deltaTime, camera, lastPos, firstMouse);
		CalcDeltaTime(deltaTime, lastFrame);

		ClearScreen();

		basicModelProgram.Use();

		glm::mat4 viewMatrix = camera.GetViewMatrix();
		glm::mat4 modelMatrix = glm::mat4(1.0);
		glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
		
		glUniformMatrix4fv(basicModelProgram.GetUniformLocation("MVP"), 1, GL_FALSE, &mvp[0][0]);

		
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(textureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		window.Postframe();
	}

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteTextures(1, &textureID);

	return 0;
}
