#pragma once

#include "FrameBuffer.h"

class UserInterfaceManager
{
public:
	void Update();
	void ShutDown();
	void Init(GLFWwindow *mWindow);
	void Render();

	//void BindFrameBuffer() const;
	//void UnbindFrameBuffer() const;	
	//std::unique_ptr<FrameBuffer> framebuffer;

	//static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:
	void configureUserInterface();
	void setBackupContext();
	
	//ImGuiViewport* m_viewport;
	//GLFWwindow* m_Window;
};
