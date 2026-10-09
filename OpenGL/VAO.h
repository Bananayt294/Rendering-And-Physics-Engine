#ifndef GLAD_GL_VERSION_1_2
#define GLAD_GL_VERSION_1_2 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "VBO.h"

class VAO {
public:
	GLuint ID{ 0 };
	VAO();
	void LinkVBO(VBO& VBO, GLuint layout);
	void bind();
	void unbind();
	void Delete();
};

#endif
