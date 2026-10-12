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
	pos = vel * deltaTime;
	vel = acc * deltaTime;


}