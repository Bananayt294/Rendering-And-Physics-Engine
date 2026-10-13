#pragma once
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
#include <memory>
#include <string>

class Model {
private:
	std::string vertexShaderPath;
	std::string fragmentShaderPath;
	std::unique_ptr<Shader> ShaderProgram;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<VAO> VAO1;
	std::unique_ptr<VBO> VBO1;
	std::unique_ptr<EBO> EBO1;

	GLuint texture = 0;
	GLint tex0Uni = -1;
	GLint modelUni = -1;
protected:
	int vertexCount;
	int indexCount;
	std::vector<GLfloat> vertexData;
	std::vector<GLuint> indexData;
	std::vector<GLfloat> textureCoords;
	glm::vec3* normalData = nullptr;
	glm::mat4 ModelMatrix;
public:
	GLFWwindow* window = nullptr;
	Model(
		int vertexCount,
		int indexCount,
		std::vector<GLfloat> incomingVertices,
		std::vector<GLuint> incomingIndices,
		std::vector<GLfloat> incomingTexCoords,
		glm::mat4 incomingModelMatrix,
		const char* vertexPath,       // Pass paths instead of a pre-built Shader object
		const char* fragmentPath
	);
	const int GetVertexCount();
	const int GetIndexCount();
	const int GetVertexDataSize();
	const int GetTextureCoordsSize();
	const int GetIndexDataSize();
	const int GetNormalDataSize();
	const std::vector<GLfloat> GetVertexData();
	const std::vector<GLuint> GetIndicesData();
	glm::vec3 GetNormalData();
	glm::mat4 GetModelMatrix();

	std::string texturePath = "None";

	GLuint VertexArrayID;
	GLuint VertexBufferID;
	GLuint IndexBufferID;
	GLuint NormalBufferID;
	GLuint TextureBufferID;
	GLuint TextureObjectID;
	bool shouldClose = false;

	void setModelMatrix(glm::mat4 ModelMatrix);
	void GenerateSphere(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, float radius, int resolution);
	void init();
	void render();
	~Model();
};