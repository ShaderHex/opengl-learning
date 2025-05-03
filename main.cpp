#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "EBO.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"

// Vertices coordinates
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f, // bottom-left corner
    0.5f, -0.5f, 0.0f, // bottom-right corner
    0.5f,  0.5f, 0.0f, // top-right corner
    -0.5f,  0.5f, 0.0f  // top-left corner
};    

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // First triangle: bottom-left, bottom-right, top-right
    2, 3, 0 // Second triangle: top-right, top-left, bottom-left
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

    Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    while (!glfwWindowShouldClose(window)) {
        
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        // Handles any types of change like resize and more
        glfwPollEvents();
    }

    std::cout << "About to delete VAO\n";
    VAO1.Delete();
    std::cout << "Deleted VAO\n";
    
    std::cout << "VBO ID = " << VBO1.ID << std::endl;
    VBO1.Delete();
    std::cout << "Deleted VBO\n";
    
    std::cout << "About to delete EBO\n";
    EBO1.Delete();
    std::cout << "Deleted EBO\n";
    

    // De-Init and closes
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}