#include "BodySystem.h"

BodySystem::BodySystem() {
	bodies.reserve(10);
}

void BodySystem::addBody(Body* body) {
	bodies.push_back(body);
}

void BodySystem::updateBodies(float deltaTime) {
	for (auto Body : bodies) {

		//Gravity
		//Body->GetPhBody()->applyForce(glm::vec3(0.0f, -9.8f, 0.0f) * Body->GetPhBody()->mass);
		Body->SetPhBodyPos(Body->GetPhBodyPos() + Body->GetPhBodyVel() * deltaTime);
		Body->SetPhBodyVel(Body->GetPhBodyVel() + Body->GetPhBodyAcc() * deltaTime);

		Body->SetPhBodyAngVel(Body->GetPhBodyAngVel() + Body->GetPhBodyAngAcc()	 * deltaTime);

		glm::quat deltaOrientation = 0.5f * Body->GetPhBodyOrientation() * deltaTime * glm::quat(0.0f, Body->GetPhBodyAngVel().x, Body->GetPhBodyAngVel().y, Body->GetPhBodyAngVel().z);
		Body->SetPhBodyOrientation(glm::normalize(Body->GetPhBodyOrientation() + deltaOrientation));
	}
}

//void BodySystem::detectCollisions(float deltaTime) {
//    for (size_t i = 0; i < bodies.size(); i++) {
//        std::shared_ptr<PhysicsBody> phBody = bodies[i]->GetPhBody();
//        if (!phBody) continue;
//
//        for (size_t j = i + 1; j < bodies.size(); j++) {
//            std::shared_ptr<PhysicsBody> otherBody = bodies[j]->GetPhBody();
//            if (!otherBody) continue;
//
//            // Calculate distance between the centers of the two spheres
//            float distance = glm::distance(phBody->pos, otherBody->pos);
//
//            // The collision threshold for two spheres is the sum of their radii
//            float collisionThreshold = phBody->radius + otherBody->radius;
//
//            if (distance < collisionThreshold) {
//                // Resolve collision between these two specific spheres
//                resolveCollisions(phBody.get(), otherBody.get());
//            }
//        }
//    }
//}

//void BodySystem::resolveCollisions(PhysicsBody* body1, PhysicsBody* body2) {
//    if (!body1 || !body2) return;
//
//    glm::vec3 relativePos = body2->pos - body1->pos;
//    float distance = glm::length(relativePos);
//
//    if (distance == 0.0f) return; // Prevent division by zero if centers overlap completely
//
//    // Normal vector pointing from body1 to body2
//    glm::vec3 normal = glm::normalize(relativePos);
//
//    // Precise contact point on the surface between the two spheres
//    glm::vec3 contactPoint = body1->pos + (normal * body1->radius);
//
//    // Relative velocity
//    glm::vec3 relativeVel = body2->vel - body1->vel;
//
//    // Velocity along the normal
//    float velAlongNormal = glm::dot(relativeVel, normal);
//
//    // Do not resolve if they are moving away from each other
//    if (velAlongNormal > 0) return;
//
//    // Restitution (bounciness: 0 = no bounce, 1 = perfectly elastic)
//    float restitution = 0.7f;
//
//    // Impulse scalar calculation
//    float impulseScalar = -(1.0f + restitution) * velAlongNormal;
//    impulseScalar /= 2.0f; // Assuming equal mass; adjust if you factor in mass
//
//    // Apply impulse to change velocities
//    glm::vec3 impulse = impulseScalar * normal;
//    body1->vel -= impulse;
//    body2->vel += impulse;
//
//    // --- Positional Correction (Fixes sinking/overlapping) ---
//    // Calculate how much the spheres are overlapping
//    float penetration = (body1->radius + body2->radius) - distance;
//    if (penetration > 0.0f) {
//        float percent = 0.5f; // Push them apart equally
//        glm::vec3 correction = (penetration * percent) * normal;
//        body1->pos -= correction;
//        body2->pos += correction;
//    }
//}