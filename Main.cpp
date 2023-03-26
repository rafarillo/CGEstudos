#include <stdio.h>
#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"

Window mainWindow;
// IBO = iondex bufffer array
const float toRadians = 3.14159265f / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

int direction = 1;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.0005f;

// Vertex Shader

static const char* vShader = "Shaders/shader1.vert";

static const char* fShader = "Shaders/shader1.frag";

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void CreateObject()
{
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 6);
	meshList.push_back(obj1);

}

int main()
{
	
	mainWindow = Window(800, 600);
	mainWindow.Intialise();

	CreateObject();
	CreateShaders();

	GLuint xMin, xMax, yMin, yMax;
	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	xMin = xMax = yMin = yMax = 0;
	while (!mainWindow.getShouldClose())
	{
		// Get + Handle user input events
		glfwPollEvents();

		// clear window
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		
		xMin = shaderList[0].GetXMin();
		xMax = shaderList[0].GetXMax();
		yMin = shaderList[0].GetYMin();
		yMax = shaderList[0].GetYMax();

		glUniform1f(xMin, -2.0f);
		glUniform1f(xMax, 2.0f);
		glUniform1f(yMin, -2.0f);
		glUniform1f(yMax, 2.0f);

		meshList[0]->RenderMesh();

		glUseProgram(0);

		// Swap the scene that is being drawn with the scene that is being seen
		mainWindow.SwapBuffers();
	}


	return 0;
}