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