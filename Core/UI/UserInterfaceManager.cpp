#include "UserInterfaceManager.h"

float static clamp(float value, float min, float max) {
    return (value < min) ? min : (value > max) ? max : value;
}

void UserInterfaceManager::ConfigureImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigDockingWithShift = true;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_GLFWwindow, true);
    ImGui_ImplOpenGL3_Init();

    //glfwSetFramebufferSizeCallback(m_GLFWwindow, framebuffer_size_callback);
}

void UserInterfaceManager::Update()
{
    initImGui();
}

void UserInterfaceManager::initImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    drawUI();
    renderImGui();
}

void UserInterfaceManager::ShutDown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UserInterfaceManager::renderImGui()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    setBackupContext();
}

void UserInterfaceManager::setBackupContext()
{
    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
}

void UserInterfaceManager::drawUI()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_viewport= ImGui::GetMainViewport();
    ImVec2 minBound = m_viewport->Pos;
    ImVec2 maxBound = ImVec2(m_viewport->Pos.x + m_viewport->Size.x, m_viewport->Pos.y + m_viewport->Size.y);

    ImGui::NewFrame();
        ImGui::Begin("Scene");
        {
            ImVec2 windowPos = ImGui::GetWindowPos();                            
            ImVec2 windowSize = ImGui::GetWindowSize();

            ImVec2 clampedPos = {
               clamp(windowPos.x, minBound.x, maxBound.x - windowSize.x),
               clamp(windowPos.y, minBound.y, maxBound.y - windowSize.y)
            };

            if (windowPos.x != clampedPos.x || windowPos.y != clampedPos.y)
                ImGui::SetWindowPos(clampedPos);

            const float width = ImGui::GetContentRegionAvail().x;
            const float height = ImGui::GetContentRegionAvail().y;

            framebuffer->RescaleFrameBuffer(1920, 1080);
            glViewport(0, 0, 1920, 1080);

            ImVec2 pos = ImGui::GetCursorScreenPos();

            ImGui::GetWindowDrawList()->AddImage(
                (void*)framebuffer->textureId,
                ImVec2(pos.x, pos.y),
                ImVec2(pos.x + 1920, pos.y + 1080),
                ImVec2(0, 1),
                ImVec2(1, 0)
            );
        }
        ImGui::End();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Demo");
            ImGui::Text("Hello Demo!");
        ImGui::End();

        ImGui::Begin("Test");
            ImGui::Text("Hello Test!");
        ImGui::End();
    ImGui::EndFrame();
}

void UserInterfaceManager::BindFrameBuffer() const
{
    framebuffer->Bind();
}

void UserInterfaceManager::UnbindFrameBuffer() const
{
    framebuffer->Unbind();
}

void UserInterfaceManager::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
