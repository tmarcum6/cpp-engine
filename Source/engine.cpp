#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "common.h"

    //void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    //void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    //void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    //    
    //// screen settings
    //const unsigned int SCR_WIDTH = 1920;
    //const unsigned int SCR_HEIGHT = 1080;
    //float lastX = SCR_WIDTH / 2.0f;
    //float lastY = SCR_HEIGHT / 2.0f;
    //bool firstMouse = true;

    //glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{
    Window window;
    window.Init("Engine", window.SCR_WIDTH, window.SCR_HEIGHT);

    // glfwSetFramebufferSizeCallback(m_GLFWwindow, framebuffer_size_callback);
    // glfwSetCursorPosCallback(m_GLFWwindow, mouse_callback);
    // glfwSetScrollCallback(m_GLFWwindow, scroll_callback);

    Shader firstShader("./Graphics/Shaders/color_by_vertices_shader.vs", "./Graphics/Shaders/color_by_vertices_shader.fs");
    Shader lightShader("./Graphics/Shaders/light_shader.vs", "./Graphics/Shaders/light_shader.fs");

    unsigned int VAO, lightVAO;
    glGenVertexArrays(1, &VAO);
    VertexBuffer vb(VertexBuffer::vertices, sizeof(VertexBuffer::vertices)); // INIT VertexBuffer in VB class
    glBindVertexArray(VAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Render render;
    render.LoadTexture("./Graphics/Textures/container.jpg");

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    firstShader.Use();
    glUniform1i(glGetUniformLocation(firstShader.ID, "texture1"), 0);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    vb.Bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    lightShader.Use();
    lightShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    lightShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

    // render loop
    while (!window.ShouldClose())
    {
        window.ProcessEvents(camera);
        window.init_ImGui();
        render.Update();
        firstShader.Use();

        // create transformations
        glm::mat4 view = camera.GetViewMatrix(); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)window.SCR_WIDTH / (float)window.SCR_HEIGHT, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(firstShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(firstShader.ID, "view");
        unsigned int projectionLoc = glGetUniformLocation(firstShader.ID, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

        glBindVertexArray(VAO);

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

        window.render_ImGui();
        window.Update();
    }

    window.close_ImGui();

    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(firstShader.ID);

    window.Shutdown();
    return 0;
}

//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
//    
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
//{
//    float xpos = static_cast<float>(xposIn);
//    float ypos = static_cast<float>(yposIn);
//    
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//    
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos;
//    
//    lastX = xpos;
//    lastY = ypos;
//    
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//    
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}

#endif