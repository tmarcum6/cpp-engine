#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// screen settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// shaders
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
" vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
"}\0";

const char* vertexShaderSourceColorByVertices = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 vertexColor;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos, 1.0);\n"
" vertexColor = aColor;\n"
"}\0";

const char* fragmentShaderSourceOrange = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
" FragColor = vertexColor;\n"
"}\n\0";

const char* fragmentShaderSourceDynamic = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
" FragColor = ourColor;\n"
"}\n\0";

const char* fragmentShaderSourceColorByVertices = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 vertexColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(vertexColor, 1.0);\n"
"}\n\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine", NULL, NULL);

    if (window == NULL)
    {
		cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
		cout << "Failed to initialize GLAD" << endl;
		return -2;
    }

	// configure vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // shader compilation error handling
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // configure vertex shader
    unsigned int vertexShaderColorByVertices = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderColorByVertices, 1, &vertexShaderSourceColorByVertices, NULL);
    glCompileShader(vertexShaderColorByVertices);

    // shader compilation error handling
    glGetShaderiv(vertexShaderColorByVertices, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderColorByVertices, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEXCOLORBYVERTICES::COMPILATION_FAILED\n" << infoLog << endl;
    }
    ////////////////////////////////////////////	// configure fragment shader orange
    unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);
    glCompileShader(fragmentShaderOrange);
	// shader compilation error handling    glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
		cout << "ERROR::SHADER::ORANGE::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // link shaders
    unsigned int shaderProgramOrange = glCreateProgram();
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);
	// shader linking error handling
    glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);
	if (!success) 
	{
        glGetProgramInfoLog(shaderProgramOrange, 512, NULL, infoLog);
		cout << "ERROR::SHADER::ORANGE::PROGRAM::LINK_FAILED\n" << infoLog << endl;
    }
    //////////////////////////////////////////////    // configure fragment shader dynamic
    unsigned int fragmentShaderDynamic = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderDynamic, 1, &fragmentShaderSourceDynamic, NULL);
    glCompileShader(fragmentShaderDynamic);
    // shader compilation error handling    glGetShaderiv(fragmentShaderDynamic, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderDynamic, 512, NULL, infoLog);
        cout << "ERROR::SHADER::DYNAMIC::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // link shaders
    unsigned int shaderProgramDynamic = glCreateProgram();
    glAttachShader(shaderProgramDynamic, vertexShader);
    glAttachShader(shaderProgramDynamic, fragmentShaderDynamic);
    glLinkProgram(shaderProgramDynamic);
    // shader linking error handling
    glGetProgramiv(shaderProgramDynamic, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgramDynamic, 512, NULL, infoLog);
        cout << "ERROR::SHADER::DYNAMIC::PROGRAM::LINK_FAILED\n" << infoLog << endl;
    }
    //////////////////////////////////////////////    // configure fragment shader color by vertices
    unsigned int fragmentShaderColorByVertices = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderColorByVertices, 1, &fragmentShaderSourceColorByVertices, NULL);
    glCompileShader(fragmentShaderColorByVertices);
    // shader compilation error handling    glGetShaderiv(fragmentShaderColorByVertices, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderColorByVertices, 512, NULL, infoLog);
        cout << "ERROR::SHADER::BYVERTICES::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // link shaders
    unsigned int shaderProgramColorByVertices = glCreateProgram();
    glAttachShader(shaderProgramColorByVertices, vertexShaderColorByVertices);
    glAttachShader(shaderProgramColorByVertices, fragmentShaderColorByVertices);
    glLinkProgram(shaderProgramColorByVertices);
    // shader linking error handling
    glGetProgramiv(shaderProgramColorByVertices, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgramColorByVertices, 512, NULL, infoLog);
        cout << "ERROR::SHADER::BYVERTICES::PROGRAM::LINK_FAILED\n" << infoLog << endl;
    }    ////////////////////////////////////////////

    glDeleteShader(vertexShader);
    glDeleteShader(vertexShaderColorByVertices);
    glDeleteShader(fragmentShaderOrange);    glDeleteShader(fragmentShaderDynamic);    glDeleteShader(fragmentShaderColorByVertices);    // two triangles with their own VAO & VBO
    float firstTriangle[] = {
        // positions        // colors
       -0.1f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
       -0.2f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
    };    float secondTriangle[] = {
         0.1f, -0.5f, 0.0f, // left  2
         0.5f, -0.5f, 0.0f, // right 2
         0.2f,  0.5f, 0.0f  // top   2
    };	// two triangles
    //float vertices[] = {
    //    -0.5f, -0.5f, 0.0f, // left  1
    //    -0.1f, -0.5f, 0.0f, // right 1
    //    -0.2f,  0.5f, 0.0f,  // top  1
    //     0.1f, -0.5f, 0.0f, // left  2
    //     0.5f, -0.5f, 0.0f, // right 2
    //     0.2f,  0.5f, 0.0f  // top   2
    //};

    // triangle
    //float vertices[] = {
    //    -0.5f, -0.5f, 0.0f, // left  
    //     0.5f, -0.5f, 0.0f, // right 
    //     0.0f,  0.5f, 0.0f  // top   
    //};

    // rectangle
    //float vertices[] = {
    //    0.5f, 0.5f, 0.0f, // top right
    //    0.5f, -0.5f, 0.0f, // bottom right
    //    -0.5f, -0.5f, 0.0f, // bottom left
    //    -0.5f, 0.5f, 0.0f // top left
    //};
    //unsigned int indices[] = { // note that we start from 0!
    //    0, 1, 3, // first triangle
    //    1, 2, 3 // second triangle
    //};
    // define vertex attribute and vertex buffer objects
    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // define the element buffer object for indexed drawing
    //unsigned int EBO;
    //glGenBuffers(1, &EBO);
    //// bind the indices to the EBO
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // unbinding
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        glUseProgram(shaderProgramColorByVertices);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // using a uniform - color change over time 
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgramDynamic, "ourColor");
        glUseProgram(shaderProgramDynamic);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, VAOs);
    glDeleteBuffers(1, VBOs);
    glDeleteProgram(shaderProgramOrange);
    glDeleteProgram(shaderProgramDynamic);
    glDeleteProgram(shaderProgramColorByVertices);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
