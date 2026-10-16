#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(float mass) {
	this -> mass = mass;
	this -> mass_inv = 1.0f / mass;
	this -> pos = glm::vec3(0.0f, 0.0f, 0.0f);
	this -> vel = glm::vec3(0.0f, 0.0f, 0.0f);
	this -> acc = glm::vec3(0.0f, 0.0f, 0.0f);
	this -> angVel = glm::vec3(0.0f, 0.0f, 0.0f);
	this -> angAcc = glm::vec3(0.0f, 0.0f, 0.0f);
	this -> inertia = glm::mat3(1.0f);
	this-> inertia_inv = glm::inverse(inertia);
	this->orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}

void PhysicsBody::updateState(float deltaTime) {
    if (deltaTime <= 0.0f) {
        return;
    }

    // 1. Update linear velocity.
    vel += acc * deltaTime;

    // 2. Update position using the new velocity.
    pos += vel * deltaTime;

    // 3. Update angular velocity.
    angVel += angAcc * deltaTime;

    // 4. Integrate angular velocity into orientation.
    float angularSpeed = glm::length(angVel);

    if (angularSpeed > 1e-6f) {
        glm::vec3 axis = angVel / angularSpeed;

        glm::quat deltaRotation = glm::angleAxis(
            angularSpeed * deltaTime,
            axis
        );

        orientation = glm::normalize(
            deltaRotation * orientation
        );
    }
}

void PhysicsBody::applyForce(glm::vec3 Force) {
    this->acc += Force * this->mass_inv;
};

void PhysicsBody::applyTorque(glm::vec3 torque) {
    this->angAcc += torque * this->inertia_inv;
};

void PhysicsBody::applyForceOnKeyPress(GLFWwindow* window){
    glm::vec3 currentAcc = this->acc;
    glm::vec3 currentVelocity = this->vel;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        applyForce(glm::vec3(0.01, 0.0, 0.0));
    }
    else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        applyForce(glm::vec3(-0.01, 0.0, 0.0));
    }
    else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        applyForce(glm::vec3(0.0, 0.01, 0.0));
    }
    else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        applyForce(glm::vec3(0.0, -0.01, 0.0));
    }
    else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        applyForce(glm::vec3(0.0, 0.0, 0.01));
    }
    else if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        applyForce(glm::vec3(0.0, 0.0, -0.01));
    }
    else {
        this->acc = glm::vec3(0.0f);
        this->vel = glm::vec3(0.0f);
    }
}

void PhysicsBody::applyTorqueOnKeyPress(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        applyTorque((glm::vec3(0.01, 0.0, 0.0)));
    }
    else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        applyTorque((glm::vec3(-0.01, 0.0, 0.0)));
    }
    else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        applyTorque((glm::vec3(0.0, 0.01, 0.0)));
    }
    else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        applyTorque((glm::vec3(0.0, -0.01, 0.0)));
    }
    else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        applyTorque((glm::vec3(0.0, 0.0, 0.01)));
    }
    else if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        applyTorque((glm::vec3(0.0, 0.0, -0.01)));
    }
    else {
        angVel = glm::vec3(0.0, 0.0, 0.0);
        angAcc = glm::vec3(0.0, 0.0, 0.0);
    }
}
