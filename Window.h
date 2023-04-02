#pragma once
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Window
{
public:
	static double xMin, xMax, yMin, yMax;
	static double MouseXPos, MouseYPos;
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	void SwapBuffers() { glfwSwapBuffers(mainWindow); }


	int Intialise();
	~Window();

private:
	GLFWwindow* mainWindow;
	static float changeRate;

	static GLint width, height;
	static GLfloat lastX, lastY;

	GLint bufferWidth, bufferHeight;

	static bool leftPressed, deslocating;

	void CreateCallbacks();
	static void ZoomCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void DragCallback(GLFWwindow* window, int button, int action, int mods);
	static void CursorCallback(GLFWwindow* window, double xPos, double yPos);

};

