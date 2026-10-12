#include "Model.h"
//
//const std::vector<GLfloat>* GetVertexData();
//const std::vector<GLuint>* GetIndicesData();
//glm::vec3* GetNormalData();
//glm::mat4 GetModelMatrix();

Model::Model(
	int vertexCount,
	int indexCount,
	std::vector<GLfloat> incomingVertices,
	std::vector<GLuint> incomingIndices,
	std::vector<GLfloat> incomingTexCoords,
	glm::mat4 incomingModelMatrix,
	const char* vertexPath,       // Pass paths instead of a pre-built Shader object
	const char* fragmentPath
)
	: vertexCount(vertexCount),
	indexCount(indexCount),
	vertexData(std::move(incomingVertices)),   // Efficiently takes full ownership
	indexData(std::move(incomingIndices)),
	textureCoords(std::move(incomingTexCoords)),
	ModelMatrix(incomingModelMatrix),
	shader(vertexPath, fragmentPath) {
};         // Safely constructs the GPU program immediately


const int Model::GetVertexCount() {
	return this->vertexCount;
}

const int Model::GetIndexCount() {
	return this->indexCount;
}

const int Model::GetVertexDataSize() {
	return vertexData.size() * sizeof(GLfloat);
}

const int Model::GetIndexDataSize() {
	return indexData.size() * sizeof(GLuint);
}

const int Model::GetTextureCoordsSize() {
	if (!textureCoords.size()) {
		return 0;
	}
	return textureCoords.size() * sizeof(GLfloat);
};

const int Model::GetNormalDataSize() {
	if (!normalData) {
		return 0;
	}
	return sizeof(*normalData);
};

const std::vector<GLfloat> Model::GetVertexData() {
	return vertexData;
};

const std::vector<GLuint> Model::GetIndicesData() {
	return indexData;
}

glm::mat4 Model::GetModelMatrix() {
	return this->ModelMatrix;
}

void Model::setShader(Shader Shader) {
	this->shader = Shader;
};

void Model::setModelMatrix(glm::mat4 ModelMatrix) {
	this->ModelMatrix = ModelMatrix;
};

void GenerateSphere(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, float radius, int resolution) {
	vertices.clear();
	indices.clear();

	for (int lat = 0; lat <= resolution; lat++) {
		float phi = glm::pi<float>() * lat / resolution;

		for (int lon = 0; lon <= resolution; lon++) {
			float theta = glm::two_pi<float>() * lon / resolution;

			// Position
			float x = radius * std::sin(phi) * std::cos(theta);
			float y = radius * std::cos(phi);
			float z = radius * std::sin(phi) * std::sin(theta);

			// Color (RGB)
			float r = 1.0f;
			float g = 1.0f;
			float b = 1.0f;

			// Texture coordinates (UV)
			float u = (float)lon / resolution;
			float v = 1.0f - (float)lat / resolution;

			// Store 8 floats per vertex:
			// x, y, z, r, g, b, u, v
			vertices.insert(vertices.end(), {
				x, y, z,
				r, g, b,
				u, v
				});
		}
	}

	// Connect the vertices into triangles
	for (int lat = 0; lat < resolution; lat++) {
		for (int lon = 0; lon < resolution; lon++) {
			GLuint first = lat * (resolution + 1) + lon;
			GLuint second = first + resolution + 1;

			indices.insert(indices.end(), {
				first, second, first + 1,
				second, second + 1, first + 1
				});
		}
	}
}


void Model::init() {
    const unsigned int width = 900;
    const unsigned int height = 900;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window as a Model member.
    window = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);

    if (window == nullptr) {
        std::cerr << "Failed to create Window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        glfwDestroyWindow(window);
        window = nullptr;
        glfwTerminate();
        return;
    }

    glViewport(0, 0, width, height);

    // Generate sphere geometry.
    // Use 64 while testing; increase it later if needed.
    GenerateSphere(vertexData, indexData, 1.5f, 64);

    vertexCount = static_cast<int>(vertexData.size() / 8);
    indexCount = static_cast<int>(indexData.size());

    // Create the shader AFTER initializing the OpenGL context.
    ShaderProgram = std::make_unique<Shader>(
        "default.vert.glsl",
        "default.frag.glsl"
    );

    // Create and configure buffers.
    VAO1 = std::make_unique<VAO>();
    VAO1->bind();

    VBO1 = std::make_unique<VBO>(
        vertexData.data(),
        GetVertexDataSize()
    );

    EBO1 = std::make_unique<EBO>(
        indexData.data(),
        GetIndexDataSize()
    );

    VAO1->LinkAttrib(
        *VBO1, 0, 3, GL_FLOAT,
        8 * sizeof(float), (void*)0
    );

    VAO1->LinkAttrib(
        *VBO1, 1, 3, GL_FLOAT,
        8 * sizeof(float), (void*)(3 * sizeof(float))
    );

    VAO1->LinkAttrib(
        *VBO1, 2, 2, GL_FLOAT,
        8 * sizeof(float), (void*)(6 * sizeof(float))
    );

    VAO1->unbind();
    VBO1->Unbind();

    // Do not unbind EBO1 here.
    // Its element-buffer binding belongs to VAO1.

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Load the texture.
    stbi_set_flip_vertically_on_load(true);

    int widthImg = 0;
    int heightImg = 0;
    int numColCh = 0;

    unsigned char* bytes = stbi_load(
        "brick.png",
        &widthImg,
        &heightImg,
        &numColCh,
        0
    );

    const unsigned char whitePixel[] = { 255, 255, 255, 255 };
    const unsigned char* pixels = bytes;

    GLenum format = GL_RGBA;

    if (!bytes) {
        std::cerr << "Failed to load brick.png: "
            << stbi_failure_reason() << '\n';

        // Use a white pixel instead of invalid image data.
        pixels = whitePixel;
        widthImg = 1;
        heightImg = 1;
        format = GL_RGBA;
    }
    else {
        switch (numColCh) {
        case 1: format = GL_RED;  break;
        case 2: format = GL_RG;   break;
        case 3: format = GL_RGB;  break;
        case 4: format = GL_RGBA; break;
        }
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST
    );
    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST
    );
    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT
    );
    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT
    );

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        widthImg,
        heightImg,
        0,
        format,
        GL_UNSIGNED_BYTE,
        pixels
    );

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    ShaderProgram->Activate();

    tex0Uni = glGetUniformLocation(ShaderProgram->ID, "tex0");

    if (tex0Uni >= 0) {
        glUniform1i(tex0Uni, 0);
    }

    // Keep the camera as a Model member too.
    camera = std::make_unique<Camera>(
        width,
        height,
        glm::vec3(0.0f, 0.0f, 5.0f)
    );
}
void Model::render() {
    if (window == nullptr ||
        !ShaderProgram ||
        !camera ||
        !VAO1) {
        return;
    }

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ShaderProgram->Activate();

    camera->Inputs(window);

    if (tex0Uni >= 0) {
        glUniform1i(tex0Uni, 0);
    }

    camera->matrix(
        45.0f,
        0.1f,
        100.0f,
        *ShaderProgram,
        "camMatrix"
    );

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    VAO1->bind();

    glDrawElements(
        GL_TRIANGLES,
        static_cast<GLsizei>(indexCount),
        GL_UNSIGNED_INT,
        nullptr
    );

    glfwSwapBuffers(window);
    glfwPollEvents();
}

Model::~Model()
{
    if (window != nullptr) {
        // Ensure this window's OpenGL context is current.
        glfwMakeContextCurrent(window);

        // Delete the texture while the context still exists.
        if (texture != 0) {
            glDeleteTextures(1, &texture);
            texture = 0;
        }

        // Release GPU resources while the context is alive.
        VAO1.reset();
        EBO1.reset();
        VBO1.reset();
        ShaderProgram.reset();

        // Release the camera.
        camera.reset();

        // Destroy the window last.
        glfwDestroyWindow(window);
        window = nullptr;

        glfwTerminate();
    }
}