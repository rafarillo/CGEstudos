#include "Window.h"

double Window::MouseXPos = 0.0f;
double Window::MouseYPos = 0.0f;

double Window::xMin = -2.0f;
double Window::xMax = 2.0f;
double Window::yMin = -2.0f;
double Window::yMax = 2.0f;

float Window::changeRate = 1.1f;

GLint Window::height = 0;
GLint Window::width = 0;

GLfloat Window::lastX = 0.0f;
GLfloat Window::lastY = 0.0f;


bool Window::leftPressed = false;
bool Window::deslocating = false;


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

	//Handle input
	CreateCallbacks();

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

void Window::CreateCallbacks()
{
	glfwSetScrollCallback(mainWindow, ZoomCallback);
	glfwSetMouseButtonCallback(mainWindow, DragCallback);
	glfwSetCursorPosCallback(mainWindow, CursorCallback);
}

void Window::ZoomCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	// Mouse represents the new center

	if (yoffset > 0)
	{
		xMin *= changeRate;
		xMax *= changeRate;
		yMin *= changeRate;
		yMax *= changeRate;
	}
	if (yoffset < 0)
	{
		xMin *= 1.0/changeRate;
		xMax *= 1.0/changeRate;
		yMin *= 1.0/changeRate;
		yMax *= 1.0/changeRate;
	}

	printf("xMin = %f xMax = %f | yMin = %f yMax = %f\n", xMin, xMax, yMin, yMax);
}

void Window::DragCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		leftPressed = true;
		printf("Press\n");
	}

	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		leftPressed = false;
		deslocating = false;
		printf("Soltou\n");
	}
}

void Window::CursorCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (leftPressed)
	{
		double myX = (xPos / width - 0.5) * (xMax - xMin);
		double myY = (1 - yPos / height - 0.5) * (yMax - yMin);
		
		if(!deslocating)
		{
			lastX = myX;
			lastY = myY;
		}
		
		deslocating = true;

		xMin += (myX - lastX);
		xMax += (myX - lastX);

		yMin += (myY - lastY);
		yMax += (myY - lastY);

		
		printf("%f, %f\n", myX, myY);
	}
}


