#ifndef WINDOW_H
#define WINDOW_H

#include "common.h"

class Window
{
public:
	// screen settings
	const unsigned int SCR_WIDTH = 1920;
	const unsigned int SCR_HEIGHT = 1080;
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;

	Window() 
	{
		glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine", NULL, NULL);
	};

private:
	GLFWwindow* m_GLFWwindow;
		
};
#endif