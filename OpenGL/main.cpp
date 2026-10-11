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
#include "Camera.h"

const unsigned int width = 900;
const unsigned int height = 900;


int main() {
	//initialize glfw
	glfwInit();
	//Give the glfw Window hints to use OpenGL 3.3 and the core version of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		// COORDINATES		//COLORS (RGB)	//TEX COORDS
		-0.5f, -0.5f,  0.5f,  1, 0, 0,		0, 0, // 0
		-0.5f, -0.5f, -0.5f,  0, 1, 0,		0, 5, // 1
		 0.5f, -0.5f, -0.5f,  0, 1, 0,		5, 5, // 2
		 0.5f, -0.5f,  0.5f,  1, 1, 1,		5, 0, // 3

		 0.0f,  0.5f,  0.0f,  1, 1, 1,		2.5f, 2.5f
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
	
	glEnable(GL_DEPTH_TEST);
	
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	while(!glfwWindowShouldClose(window)) {
		//Clear the color and THEN assigns it to this
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clears Where the Buffer and Color will be stored ot make sure nothing from the past is left here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Activates the ShaderProgram that actually contains all the rendering for our shader
		ShaderProgram.Activate();
		//Takes Inputs From the Window
		camera.Inputs(window);
		//Sends Texture0 Which is the texture we wanna render to default.vert.glsl
		glUniform1i(tex0Uni, 0);
		//Creates The camera Matrix. Basically X,Y,Z starting coords for the camera
		camera.matrix(45.0f, 0.1f, 100.0f, ShaderProgram, "camMatrix");
		//Activates Enables A Slot To Store The Texture In
		glActiveTexture(GL_TEXTURE0);
		//A Random Set of Initialised Bytes takes that space As the Variable "texture"
		glBindTexture(GL_TEXTURE_2D, texture);
		//When VAO1 is bound then all the configs stored in them go to their designated slots in VBO goes to VBO slot,
		//EBO goes to EBO slot AND The Texture config overwrites the waste data in "texture" variable with its bytes and gets rendered
		VAO1.bind();
		//Draws Triangles
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		//swaps the back buffer where everything happened to the front buffer where it displays.
		glfwSwapBuffers(window);
		//Get and take care of all GLFW events, such as keyboard and mouse input, window resizing, etc.
		glfwPollEvents();
	}
	VAO1.Delete();
	VBO1.Delete();
	EBO1.deleteBuffer();
	glDeleteTextures(1, &texture);
	//destroy the window and terminate glfw to free up resources and memory
	glfwDestroyWindow(window);	
	glfwTerminate();
	return 0;
}
