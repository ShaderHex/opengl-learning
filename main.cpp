#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <stb/stb_image.h>

#include "EBO.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "Texture.h"

// Vertices coordinates
GLfloat vertices[] =
{
    //    Coordinate           /       Colours     //
	-0.5f,  -0.5,   0.0f,       1.0f,   0.0f,   0.0f,   0.0f, 0.0f,
    -0.5f,   0.5,   0.0f,       0.0f,   1.0f,   0.0f,   0.0f, 1.0f,
     0.5f,   0.5,   0.0f,       0.0f,   0.0f,   1.0f,   1.0f, 1.0f,
     0.5f,  -0.5,   0.0f,       1.0f,   1.0f,   1.0f,   1.0f, 0.0f
};  

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1,
    3, 0, 2
};

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main() {
    // init glfw and tells the gpu to use 3.3
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // creates window
    GLFWwindow* window = glfwCreateWindow(800, 800, "Hello Triangle", NULL, NULL);
    if (window == NULL) {
        std::cout<<"Failed to init glfw\n";
        glfwTerminate();
        return -1;
    }
    // uses the window buffer
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // Checks for resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Loads the shaders
    Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");

    // Binds VAO, VBO and EBO also unbinds
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));

    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 2, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    Texture memeImage("image.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    memeImage.texUnit(shaderProgram, "tex0", 0);

    while (!glfwWindowShouldClose(window)) {
        // Clear screen
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Uses the Shader Program
        shaderProgram.Activate();
        glUniform1f(uniID, 0.5);
        memeImage.Bind();
        // Binds VAO
        VAO1.Bind();
        // Draws on the screen
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        // Handles any types of change like resize and more
        glfwPollEvents();
    }
    // Delets VAO, VBO and EBO
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    memeImage.Unbind();
    memeImage.Delete();
    

    // De-Init and closes
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}