#include "EBO.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

EBO::EBO(GLuint * indices, GLsizeiptr size) {
	glGenBuffers(1, &this -> ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this -> ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this -> ID);
}

void EBO::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::deleteBuffer() {
	glDeleteBuffers(1, &this -> ID);
}