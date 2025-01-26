#ifndef WINDOW
#define WINDOW

#include "window.h"
#include "common.h"

void Window::Init(std::string const &windowTitle, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT)
{
    glfwInit();

    // glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    // glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_GLFWwindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, windowTitle.c_str(), NULL, NULL);
    if (m_GLFWwindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_GLFWwindow);
    // gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    //glfwSetFramebufferSizeCallback(m_GLFWwindow, framebuffer_size_callback);
    //glfwSetCursorPosCallback(m_GLFWwindow, mouse_callback);
    //glfwSetScrollCallback(m_GLFWwindow, scroll_callback);

    configure_ImGui();

    glfwSetInputMode(m_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
}

void Window::configure_ImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigDockingWithShift = true;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_GLFWwindow, true);
    ImGui_ImplOpenGL3_Init();
}

void Window::init_ImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();
}

void Window::close_ImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Window::render_ImGui()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::Update()
{
    glfwSwapBuffers(m_GLFWwindow);
    glfwPollEvents();
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(m_GLFWwindow);
}

void Window::Shutdown()
{
    // glfwDestroyWindow(m_GLFWwindow);
    glfwTerminate();
}

void Window::ProcessEvents(Camera camera)
{
    // glfwPollEvents();
    
    float currentFrame = static_cast<float>(glfwGetTime());
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;

    if (glfwGetKey(m_GLFWwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_GLFWwindow, true);
    if (glfwGetKey(m_GLFWwindow, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, m_deltaTime);
    if (glfwGetKey(m_GLFWwindow, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, m_deltaTime);
    if (glfwGetKey(m_GLFWwindow, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, m_deltaTime);
    if (glfwGetKey(m_GLFWwindow, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, m_deltaTime);
}

//void framebuffer_size_callback(GLFWwindow *window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
//    
//void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
//{
//    float xpos = static_cast<float>(xposIn);
//    float ypos = static_cast<float>(yposIn);
//    
//    if (m_firstMouse)
//    {
//        m_lastX = xpos;
//        m_lastY = ypos;
//        m_firstMouse = false;
//    }
//    
//    float xoffset = xpos - m_lastX;
//    float yoffset = m_lastY - ypos;
//    
//    m_lastX = xpos;
//    m_lastY = ypos;
//    
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//    
//void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}

#endif