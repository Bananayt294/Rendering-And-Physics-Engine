#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Shaders.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

void main() {
	//initialize glfw
	glfwInit();
	//Give the glfw Window hints to use OpenGL 3.3 and the core version of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		// 0: Bottom-left outer vertex
		-0.5f, -0.5f * float(sqrt(3)) / 3.0f, 0.0f,

		// 1: Bottom-right outer vertex
		 0.5f, -0.5f * float(sqrt(3)) / 3.0f, 0.0f,

		 // 2: Top outer vertex
		  0.0f,  0.5f * float(sqrt(3)) / 3.0f, 0.0f,

		  // 3: Midpoint on left edge (between 0 and 2)
		  -0.25f, 0.0f, 0.0f,

		  // 4: Midpoint on bottom edge (between 0 and 1)
		   0.0f, -0.5f * float(sqrt(3)) / 3.0f, 0.0f,

		   // 5: Midpoint on right edge (between 2 and 1)
			0.25f, 0.0f, 0.0f
	};

	GLuint indices[] = {
		0, 3, 4,  // Bottom-Left Triangle
		3, 2, 5,  // Top Triangle
		4, 5, 1   // Bottom-Right Triangle
	};

	//creates a glfw window which is name OpenGL and has a width and height of 800x800 pixels and is stored in the window variable and fullscreen is set to NULL or disabled
	GLFWwindow* window = glfwCreateWindow(800,800, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create Window" << std::endl;
		glfwTerminate();
		return;
	}
	//sets the context of the window we just created to be the current context of openGL so it renders to window and not some other window that may be open
	glfwMakeContextCurrent(window);
	//loads the OpenGL function pointers so we can use OpenGL functions
	gladLoadGL();

	//sets the viewport of the window to be the same size as the window so that it renders to the entire window and not just a portion of it
	glViewport(0, 0, 800, 800);

	Shader ShaderProgram("default.vert.glsl", "default.frag.glsl");

	VAO VAO1;
	VAO1.bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	
	VAO1.LinkVBO(VBO1, 0);
	VAO1.unbind();
	VBO1.Unbind();
	EBO1.unbind();


	//We Bind the VBO to the buffer and specify that it is a GL_ARRAY_BUFFER which means it is a buffer that will be used to store vertex data 
	//and we are binding it to the VBO variable so we can use it later

	//In this line we are WRITING the vertices data into the GL_ARRAY_BUFFER slot in the graphics card memory that we just bound the VBO to and 
	//we are telling it how much data we are writing, what data we are writing, and how we are going to use that data, 
	//GL_STATIC_DRAW means we are going to use this data a lot and not change it much, 
	//GL_DYNAMIC_DRAW means we are going to use this data a lot and change it a lot, 
	//and GL_STREAM_DRAW means we are going to use this data a lot and change it every frame
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//We Bind the EBO to the buffer and specify that it is a GL_ELEMENT_ARRAY_BUFFER which means it is a buffer that will be used to store index data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//In this line we basically adding the VBO to the VAO and VAO is the array the stores all the configurations of multiple different VBOs so we can switch when we want
	//But we are only using one VBO in this case so we are just adding the VBO to the VAO and telling it how to interpret the data in the VBO and how to use it
	//The first value in glVertexAttribPointer is the index of the vertex attribute we are configuring, in this case 0 because we only have one vertex attribute, the position
	//The second value is the size of the vertex attribute, in this case 3 because we have 3 values for the position, x, y, and z
	//The third value is the type of the vertex attribute, in this case GL_FLOAT because we are using floats for the position
	//The fourth value is whether or not to normalize the vertex attribute, in this case GL_FALSE because we don't want to normalize the position
	//The fifth value is the stride of the vertex attribute, in this case 3 * sizeof(float) because we have 3 values for the position and each value is a float
	//The VBO's arent really connected to the VAO, the VBO is stored in the Buffer slot of graphics card memory and VAO just stores the data that the VBO would have but not the literal VBO variable which is why we are storing vertices and etc in VAO and not directly VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//This function clears the color buffer for the graphics card and sets the color to be used when clearing the color buffer to the color we want and stores it in a variable
	glClearColor(0.07f,0.13f,0.17f,1.0f);
	//glClear uses this variable to clear and set the backbuffers color to this variable
	glClear(GL_COLOR_BUFFER_BIT);
	//glfwSwapBuffers swaps the backbuffer with the frontbuffer so that the color we just set is displayed on the window and not just in the backbuffer
	glfwSwapBuffers(window);

	while(!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ShaderProgram.Activate();
		VAO1.bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		//Get and take care of all GLFW events, such as keyboard and mouse input, window resizing, etc.
		glfwPollEvents();
	}
	VAO1.Delete();;
	VBO1.Delete();
	EBO1.deleteBuffer();
	//destroy the window and terminate glfw to free up resources and memory
	glfwDestroyWindow(window);	
	glfwTerminate();

}
