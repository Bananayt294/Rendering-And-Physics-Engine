#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class VBO {
public:
	GLuint ID = 0;
	VBO(GLfloat* vertices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();
};


