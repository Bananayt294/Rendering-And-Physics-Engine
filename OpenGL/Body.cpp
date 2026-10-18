#include "Body.h"
//
//void SetPhBodyPos(glm::vec3 newPos);
//void SetPhBodyVel(glm::vec3 newPos);
//void SetPhBodyAcc(glm::vec3 newPos);
//void SetPhBodyAngVel(glm::vec3 newPos);
//void SetPhBodyAngAcc(glm::vec3 newPos);
//void SetPhBodyInertia(glm::vec3 newPos);
//void SetPhBodyInertia_inv(glm::vec3 newPos);

Body::Body(std::string name, PhysicsBody* PHbody, Model* model) :name{ name }, phBody{ PHbody }, model{ model } {};
Body::~Body() = default;


PhysicsBody* Body::GetPhBody() {
	return this->phBody;
};
glm::vec3 Body::GetPhBodyPos() {
	return this->phBody->pos;
};
glm::vec3 Body::GetPhBodyVel() {
	return this->phBody->vel;
}
glm::vec3 Body::GetPhBodyAcc() {
	return this->phBody->acc;
}
glm::vec3 Body::GetPhBodyAngVel() {
	return this->phBody->angVel;
}
glm::vec3 Body::GetPhBodyAngAcc() {
	return this->phBody->angAcc;
}
glm::quat Body::GetPhBodyOrientation() {
	return this->phBody->orientation;
};

//glm::mat3 Body::GetPhBodyInertia() {
//	return this->phBody->inertia;
//}
//glm::mat3 Body::GetPhBodyInertia_inv() {
//	return this->phBody->inertia_inv;
//}


void Body::SetPhBodyPos(glm::vec3 newPos) {
	this->phBody->pos = newPos;
};

void Body::SetPhBodyOrientation(glm::quat NewOrientation) {
	this->phBody->orientation = NewOrientation;
};


void Body::SetPhBodyVel(glm::vec3 Vel) {
	this->phBody->vel = Vel;
};

void Body::SetPhBodyAngVel(glm::vec3 AngVel) {
	this->phBody->angVel = AngVel;
};

void Body::SetModel(Model* model) {
	this->model = model;
};

void Body::SetPhBody(PhysicsBody* phBody) {
	this->phBody = phBody;
}

void Body::renderModel() {
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), phBody->pos);
	glm::mat4 rotationMatrix = glm::toMat4(phBody->orientation);
	model->setModelMatrix(translationMatrix * rotationMatrix);
	model->render();
};

//void Body::SetPhBodyAcc(glm::vec3 Acc) {
//	this->phBody->acc = Acc;
//};
//void Body::SetPhBodyAngAcc(glm::vec3 AngAcc) {
//	this->phBody->angAcc = AngAcc;
//};
//
//void Body::SetPhBodyInertia(glm::mat3 newInertia) {
//	this->phBody->inertia = newInertia;
//};
//void SetPhBodyInertia_inv(glm::mat3 newInertia_inv) {
//	this->phBody->inertia_inv = newInertia_inv;
//};