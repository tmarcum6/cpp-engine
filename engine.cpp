#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "common.h"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{
    Window window;
    window.Init("Engine", window.SCR_WIDTH, window.SCR_HEIGHT);

    Shader firstShader("./Graphics/Shaders/color_by_vertices_shader.vs", "./Graphics/Shaders/color_by_vertices_shader.fs");

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    VertexBuffer vb(VertexBuffer::vertices, sizeof(VertexBuffer::vertices)); // INIT VertexBuffer in VB class
    glBindVertexArray(VAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load and create a texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on currently bound texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    firstShader.use();
    glUniform1i(glGetUniformLocation(firstShader.ID, "texture1"), 0);

    vb.bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // render loop
    while (!window.ShouldClose())
    {
        window.ProcessEvents(camera);
        window.init_ImGui();

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // activate shader
        firstShader.use();

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
    }

    window.close_ImGui();

    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(firstShader.ID);

    window.Shutdown();
    return 0;
}

#endif