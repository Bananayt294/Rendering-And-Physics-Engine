#pragma once
#include <vector>
#include "Body.h"
#include "Shaders.h"

class BodySystem {
public:
	BodySystem();

	std::vector<Body*> bodies;
	
	void addBody(Body* body);
	void updateBodies(float deltaTime);
	void detectCollisions(float deltaTime);
	void resolveCollisions(float deltaTime);
	void renderBodies();
	void destroyBodies();
};