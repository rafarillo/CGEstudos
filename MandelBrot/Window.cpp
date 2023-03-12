#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	bufferHeight = 0;
	bufferWidth = 0;
	mainWindow = nullptr;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	height = windowHeight;
	width = windowWidth;
	bufferHeight = 0;
	bufferWidth = 0;
	mainWindow = nullptr;

}

int Window::Intialise()
{
	// initialize GLFW

	if (!glfwInit())
	{
		printf("GLFW initialization failed");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OPENGL version

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // version >= 3.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // version <= 3.0
	// Core profile = no backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // version <= 3.0
	// Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // version <= 3.0

	mainWindow = glfwCreateWindow(width, height, "MandelBrot", NULL, NULL);
	if (!mainWindow)
	{
		printf("Creation of mainWindow failed");
		glfwTerminate();
		return 1;
	}

	// Get buffer size information

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set the context for GLEW to use
	// everything must be draw in this window
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Failed glew initialization");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	return 0;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
