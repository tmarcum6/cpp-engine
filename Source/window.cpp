#ifndef WINDOW
#define WINDOW

#include "window.h"
#include "common.h"

void Window::Init(std::string const &windowTitle, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT)
{
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
    }

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

    glfwSetWindowUserPointer(m_GLFWwindow, reinterpret_cast<void*>(this));
    glfwSetFramebufferSizeCallback(m_GLFWwindow, framebuffer_size_callback);
    glfwSetCursorPosCallback(m_GLFWwindow, mouse_callback);
    glfwSetScrollCallback(m_GLFWwindow, scroll_callback);

    configure_ImGui();

    glfwSetInputMode(m_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);

    shader = std::make_unique<Shader>("./Graphics/Shaders/color_by_vertices_shader.vs", "./Graphics/Shaders/color_by_vertices_shader.fs");
    lightShader = std::make_unique<Shader>("./Graphics/Shaders/light_shader.vs", "./Graphics/Shaders/light_shader.fs");
    m_camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

    glGenVertexArrays(1, &m_VAO);
    VertexBuffer vb(VertexBuffer::vertices, sizeof(VertexBuffer::vertices)); // INIT VertexBuffer in VB class
    glBindVertexArray(m_VAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Renderer renderer;
    renderer.LoadTexture("./Graphics/Textures/container.jpg");

    shader->Use();
    glUniform1i(glGetUniformLocation(shader->ID, "texture1"), 0);

    glGenVertexArrays(1, &m_lightVAO);
    glBindVertexArray(m_lightVAO);

    vb.Bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    lightShader->Use();
    lightShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    lightShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
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
    glfwPollEvents(); // move to ProcessEvents?
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(m_GLFWwindow);
}

void Window::Shutdown()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteProgram(shader->ID);
    glfwDestroyWindow(m_GLFWwindow);
    glfwTerminate();
}

void Window::ProcessEvents()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;

    if (glfwGetKey(m_GLFWwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_GLFWwindow, true);
    if (glfwGetKey(m_GLFWwindow, GLFW_KEY_W) == GLFW_PRESS)
        m_camera->ProcessKeyboard(FORWARD, m_deltaTime);
    if (glfwGetKey(m_GLFWwindow, GLFW_KEY_S) == GLFW_PRESS)
        m_camera->ProcessKeyboard(BACKWARD, m_deltaTime);
    if (glfwGetKey(m_GLFWwindow, GLFW_KEY_A) == GLFW_PRESS)
        m_camera->ProcessKeyboard(LEFT, m_deltaTime);
    if (glfwGetKey(m_GLFWwindow, GLFW_KEY_D) == GLFW_PRESS)
        m_camera->ProcessKeyboard(RIGHT, m_deltaTime);
}

void Window::Render()
{
    // create transformations
    glm::mat4 view = m_camera->GetViewMatrix(); // make sure to initialize matrix to identity matrix first
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(m_camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // retrieve the matrix uniform locations
    unsigned int modelLoc = glGetUniformLocation(shader->ID, "model");
    unsigned int viewLoc = glGetUniformLocation(shader->ID, "view");
    unsigned int projectionLoc = glGetUniformLocation(shader->ID, "projection");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

    glBindVertexArray(m_VAO);

    for (unsigned int i = 0; i < 10; i++)
    {
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, VertexBuffer::cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
    
void Window::mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    Window* window_ptr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    
    if (window_ptr->m_firstMouse)
    {
        window_ptr->m_lastX = xpos;
        window_ptr->m_lastY = ypos;
        window_ptr->m_firstMouse = false;
    }
    
    float xoffset = xpos - window_ptr->m_lastX;
    float yoffset = window_ptr->m_lastY - ypos;
    
    window_ptr->m_lastX = xpos;
    window_ptr->m_lastY = ypos;
    
    window_ptr->m_camera->ProcessMouseMovement(xoffset, yoffset);
}
    
void Window::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    Window* window_ptr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

    window_ptr->m_camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

#endif