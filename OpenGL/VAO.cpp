#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VAO.h"
#include <iostream>
#include "VBO.h"

VAO::VAO() {
	glGenVertexArrays(1, &this->ID);
	if (this->ID == 0) {
		std::cout << "Failed to generate VAO" << std::endl;
		return;
	}
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, const void* offset) {
	this->bind();
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
	this->unbind();
}
	
void VAO::bind() {
	glBindVertexArray(this->ID);
}

void VAO::unbind() {
	glBindVertexArray(0);
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &this->ID);
}