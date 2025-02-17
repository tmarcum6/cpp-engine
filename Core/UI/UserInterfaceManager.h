#pragma once

#include "FrameBuffer.h"

class UserInterfaceManager
{
public:
	void Update();
	void ShutDown();
	void BindFrameBuffer() const;
	void UnbindFrameBuffer() const;
	void ConfigureImGui();
	
	std::unique_ptr<FrameBuffer> framebuffer;

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:
	void initImGui();
	void renderImGui();
	void drawUI();
	void setBackupContext();
	
	GLFWwindow* m_GLFWwindow;
	ImGuiViewport* m_viewport;
};

