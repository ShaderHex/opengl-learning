#include "VAO.h"
#include "VBO.h"  // for the LinkVBO signature

VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponent, GLenum type, GLsizeiptr stride, void* offset) {
    VBO.Bind();
    glVertexAttribPointer(layout, numComponent, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind() {
    glBindVertexArray(ID);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::Delete() {
    glDeleteVertexArrays(1, &ID);
}
