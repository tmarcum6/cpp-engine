#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bitset>
#include <string>
#include "Coordinator.h"
#include "UserInterfaceManager.h"
#include <bitset>
#include <iostream>

class WindowManager
{
public:
	void Init(
		std::string const& windowTitle, unsigned int windowWidth, unsigned int windowHeight,
		unsigned int windowPositionX, unsigned int windowPositionY);

	void Update();
	void ProcessEvents();
	void Shutdown();

private:
	GLFWwindow* mWindow;
	
	UserInterfaceManager* mUserInterfaceManager;

	std::bitset<8> mButtons;
};
