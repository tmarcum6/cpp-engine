#ifndef WINDOW_H
#define WINDOW_H

#include "common.h"

class Window
{
public:
	GLFWwindow* m_GLFWwindow;
	Window(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT);
	~Window();
};
#endif