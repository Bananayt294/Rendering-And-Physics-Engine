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

void VAO::LinkVBO(VBO& VBO, GLuint layout) {
	this->bind();
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
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