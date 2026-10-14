#include "Shaders.h"
#include <fstream>
#include <sstream>
#include <string> 

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);

	if (!in.is_open()) {
		throw std::runtime_error(
			std::string("Failed to open shader file: ") + filename
		);
	}

	std::ostringstream contents;
	contents << in.rdbuf();

	if (in.bad()) {
		throw std::runtime_error(
			std::string("Failed to read shader file: ") + filename
		);
	}

	return contents.str();
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}