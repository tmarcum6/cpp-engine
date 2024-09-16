#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

using WindowPointer = std::shared_ptr<Window>;

class Window
{
	public:
		Window(const WindowID id,
			const int width,
			const int height,
			const std::string & title,
			GLFWmonitor * monitor = nullptr,
			const WindowPointer & share = WindowPointer(nullptr));
	
		void Create();

		void Initialize();
		
		bool shouldClose(GLFWwindow* GLFWwindow);

		void framebuffer_size_callback(GLFWwindow* GLFWwindow, int width, int height);
		
		void processInput(GLFWwindow* window);

	private:
		GLFWwindow* glfwWindow;
		const WindowID windowID;
};
#endif