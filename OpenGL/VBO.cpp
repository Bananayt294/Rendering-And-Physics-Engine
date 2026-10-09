#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VBO.h"
#include <iostream>
#include <string>

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &this->ID);
	if (this->ID == 0) {
		std::cout << "Failed to generate VBO" << std::endl;
		return;
	}
	Bind();
	// Upload vertex data to the VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	Unbind();
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	glDeleteBuffers(1, &this -> ID);
}
