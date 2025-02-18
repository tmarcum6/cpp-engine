#pragma once

#include "FrameBuffer.h"
#include "CameraControlSystem.h"

class UserInterfaceManager
{
public:
	void Update();
	void ShutDown();
	void Init(GLFWwindow *mWindow);
	void Render();

	void BindFrameBuffer() const;
	void UnbindFrameBuffer() const;	

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	
	std::unique_ptr<FrameBuffer> framebuffer;

private:
	void configureUserInterface();
	void setBackupContext();
	
	ImGuiViewport *m_viewport;
	CameraControlSystem m_CameraControlSystem;
};
