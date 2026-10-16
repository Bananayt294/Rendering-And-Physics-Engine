#pragma once
#include <glm/glm.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class PhysicsBody {
public:
	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 acc;
	glm::quat orientation;
	glm::vec3 angVel;
	glm::vec3 angAcc;
	glm::mat3 inertia;
	glm::mat3 inertia_inv;
	float mass;
	float mass_inv;
	PhysicsBody(float mass);
	void updateState(float deltaTime);
	void applyForce(glm::vec3 Force);
	void applyTorque(glm::vec3 Force);
	void applyForceOnKeyPress(GLFWwindow* window);
	void applyTorqueOnKeyPress(GLFWwindow* window);
};