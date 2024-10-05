#include "window.h"
#include "common.h"

Window::Window(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT)
{
    m_GLFWwindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine", NULL, NULL);
}

Window::~Window()
{
}
