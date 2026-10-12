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
#include <vector>
#include "Model.h"
const unsigned int width = 900;
const unsigned int height = 900;



int main() {
	Model model(
		0,                          // vertexCount: generated later
		0,                          // indexCount: generated later
		{},                         // incomingVertices
		{},                         // incomingIndices
		{},                         // incomingTexCoords: UVs are already in vertices
		glm::mat4(1.0f),            // identity model matrix
		"default.vert.glsl",        // vertex shader path
		"default.frag.glsl"         // fragment shader path
	);
	model.init();
	while (!glfwWindowShouldClose(model.window)) {
		model.render();
	}
	return 0;
}
