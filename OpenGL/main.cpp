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
#include "PhysicsBody.h"
#include "Body.h"
#include <string>
#include <algorithm>
#include "BodySystem.h"
const unsigned int width = 900;
const unsigned int height = 900;



int main() {
    Model model(
        0,
        0,
        {},
        {},
        {},
        glm::mat4(1.0f),
        "default.vert.glsl",
        "default.frag.glsl"
    );

    std::string name = "sphere";
    PhysicsBody sphere(2.0f);
    Body Sphere(name, &sphere, &model);
    BodySystem Bodies;
    Bodies.addBody(&Sphere);

    // Initial physics state.
    sphere.pos = glm::vec3(0.0f, 2.0f, 0.0f);
    sphere.vel = glm::vec3(0.5f, 0.0f, 0.0f);
    sphere.acc = glm::vec3(0.0f, 0.0f, 0.0f);
    sphere.angVel = glm::vec3(0.0f, 0.8f, 0.0f);

    // Initialize the OpenGL context and resources.
    model.init();

    if (model.window == nullptr) {
        return -1;
    }

    // Start measuring frame time after initialization.
    float previousTime = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(model.window)) {
        float currentTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        deltaTime = std::min(deltaTime, 0.05f);
        sphere.applyForceOnKeyPress(model.window);
        sphere.applyTorqueOnKeyPress(model.window);
        //Update physics before rendering.
        
        //sphere.updateState(deltaTime);
        Bodies.updateBodies(deltaTime);
        Sphere.renderModel();
    }

    return 0;
}