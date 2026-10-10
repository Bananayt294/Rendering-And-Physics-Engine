#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Shaders.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


const unsigned int width = 800;
const unsigned int height = 800;


int main() {
	//initialize glfw
	glfwInit();
	//Give the glfw Window hints to use OpenGL 3.3 and the core version of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		// COORDINATES					//	COLORS (RGB)		// TEX COORDS
		// 0: Bottom-left
		-0.5f, -0.5f,  0.5f,  1, 0, 0,  0, 0, // 0
		-0.5f, -0.5f, -0.5f,  0, 1, 0,  0, 5, // 1
		 0.5f, -0.5f, -0.5f,  0, 1, 0,  5, 5, // 2
		 0.5f, -0.5f,  0.5f,  1, 1, 1,  5, 0, // 3

		 0.0f,  0.5f,  0.0f,  1, 1, 1,  2.5f, 2.5f
	};

	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3, 
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

	//creates a glfw window which is name OpenGL and has a width and height of 800x800 pixels and is stored in the window variable and fullscreen is set to NULL or disabled
	GLFWwindow* window = glfwCreateWindow(width,height, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//sets the context of the window we just created to be the current context of openGL so it renders to window and not some other window that may be open
	glfwMakeContextCurrent(window);
	//loads the OpenGL function pointers so we can use OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//sets the viewport of the window to be the same size as the window so that it renders to the entire window and not just a portion of it
	glViewport(0, 0, width, height);

	Shader ShaderProgram("default.vert.glsl", "default.frag.glsl");

	VAO VAO1;
	VAO1.bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.unbind();
	VBO1.Unbind();
	EBO1.unbind();

	GLuint uniID = glGetUniformLocation(ShaderProgram.ID, "scale");


	//GLuint DistanceID = glGetUniformLocation(ShaderProgram.ID, "distance");
	//GLuint TimeID = glGetUniformLocation(ShaderProgram.ID, "time");
	//GLuint speedID = glGetUniformLocation(ShaderProgram.ID, "speed");
	// VBO and EBO data uploaded by their constructors; VAO/EBO association created while VAO was bound.
	// Vertex attributes configured above with VAO1.LinkAttrib. No extra glBufferData calls needed here.
	// Safety: ensure no accidental global buffers are bound.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//This function clears the color buffer for the graphics card and sets the color to be used when clearing the color buffer to the color we want and stores it in a variable
	glClearColor(0.07f,0.13f,0.17f,1.0f);
	//glClear uses this variable to clear and set the backbuffers color to this variable
	glClear(GL_COLOR_BUFFER_BIT);
	//glfwSwapBuffers swaps the backbuffer with the frontbuffer so that the color we just set is displayed on the window and not just in the backbuffer
	glfwSwapBuffers(window);

	//Texture
	stbi_set_flip_vertically_on_load(true);
	int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load("brick.png", &widthImg, &heightImg, &numColCh, 0);
	if (!bytes) {
		std::cout << "Failed to load texture 'brick.png': " << stbi_failure_reason() << std::endl;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLenum format = (numColCh == 4) ? GL_RGBA : (numColCh == 3) ? GL_RGB : GL_RED;
	// Ensure proper alignment for images with widths that are not multiples of 4
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, format, widthImg, heightImg, 0, format, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(ShaderProgram.ID, "tex0");
	ShaderProgram.Activate();
	glUniform1i(tex0Uni, 0);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	while(!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ShaderProgram.Activate();

		double crntTime = glfwGetTime();
		float deltaTime = static_cast<float>(crntTime - prevTime);
		prevTime = crntTime;

		rotation += 45.0f * deltaTime;

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.2f, -2.5f));
		projection = glm::perspective(glm::radians(45.0f), (float)width / (float) height, 0.1f, 100.0f); 
		//glUniform1f(uniID, 1.0f);

		int modelLoc = glGetUniformLocation(ShaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(ShaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int ProjLoc = glGetUniformLocation(ShaderProgram.ID, "projection");
		glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		VAO1.bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		//Get and take care of all GLFW events, such as keyboard and mouse input, window resizing, etc.
		glfwPollEvents();
	}
	VAO1.Delete();;
	VBO1.Delete();
	EBO1.deleteBuffer();
	glDeleteTextures(1, &texture);
	//destroy the window and terminate glfw to free up resources and memory
	glfwDestroyWindow(window);	
	glfwTerminate();
	return 0;
}
