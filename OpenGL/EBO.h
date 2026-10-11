#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class EBO {
public:
	GLuint ID{0};
	EBO(GLuint* indices, GLsizeiptr size);
	void bind();
	void unbind();
	void deleteBuffer();
};

