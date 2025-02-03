#pragma once

#include "common.h"
#include "renderer.h"
#include "framebuffer.h"
#include "vertexbuffer.h"
#include <shader.h>
#include <camera.h>
#include <memory>

class Window
{
public:
	const unsigned int SCR_WIDTH = 1920;
	const unsigned int SCR_HEIGHT = 1080;

	void Init(std::string const &windowTitle, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT);
	void Update();
	bool ShouldClose();
	void Shutdown();
	void ProcessEvents();
	void InitShaders();

	void configure_ImGui();
	void init_ImGui();
	void close_ImGui();
	void render_ImGui();
	void drawUI();
	void setBackupContext();
	void bindFrameBuffer();
	void handleTransformations();
	void updateRenderer();
	void unbindFrameBuffer();
	void useShader();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void window_size_callback_static(GLFWwindow* window, int width, int height);

	std::unique_ptr<Shader> shader;
	std::unique_ptr<Shader> lightShader;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<FrameBuffer> framebuffer;

private:
	GLFWwindow *m_GLFWwindow;
	std::unique_ptr<Camera> m_camera;
	ImGuiViewport* m_viewport;

	bool m_firstMouse = true;
	float m_lastX = SCR_WIDTH / 2.0f;
	float m_lastY = SCR_HEIGHT / 2.0f;
	float m_deltaTime = 0.0f;
	float m_lastFrame = 0.0f;

	unsigned int m_VAO, m_lightVAO;
};