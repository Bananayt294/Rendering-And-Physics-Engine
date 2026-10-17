#pragma once
#include <string>
#include "PhysicsBody.h"
#include "Model.h"
class Body {
public:

	Body(std::string name, PhysicsBody* PHbody, Model* model);
	~Body();

	PhysicsBody* GetPhBody();
	Model* GetModel() const;
	const std::string& Getname() const;
	glm::vec3 GetPhBodyPos();
	glm::quat GetPhBodyOrientation();
	glm::vec3 GetPhBodyVel();
	glm::vec3 GetPhBodyAngVel();
	glm::vec3 GetPhBodyAcc();
	glm::vec3 GetPhBodyAngAcc();

	void SetPhBodyPos(glm::vec3 newPos);
	void SetPhBodyOrientation(glm::quat NewOrientation);
	void SetPhBodyAngVel(glm::vec3 newAngVel);
	void SetPhBodyVel(glm::vec3 newVel);
	
	void SetModel(Model* NewModel);
	void SetPhBody(PhysicsBody* phBody);
	
	void renderModel();

protected:
	PhysicsBody* phBody;
	Model* model;
	std::string name;
};