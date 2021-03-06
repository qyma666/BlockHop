//
// Created by Tim on 19/04/2017.
//

#ifndef BLOCKHOP_TRANSFORMCOMPONENT_H
#define BLOCKHOP_TRANSFORMCOMPONENT_H

#include "../ecs/component.h"
#include "../ecs/ecsManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class TransformComponent : public Component<TransformComponent>
{
	glm::mat4 matrix;
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	glm::vec3 velocity;
	glm::vec3 angularVelocity;

	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;

	void genMatrix();
	void genVectors();

public:
	TransformComponent();
	~TransformComponent();
	void setValues(json inValues);

	glm::mat4 getMatrix() const;
	glm::mat4 getAlphaMatrix(const double alpha) const;
	glm::vec3 getPosition() const;
	glm::vec3 getAlphaPosition(const double alpha) const;
	void setPosition(glm::vec3 inPosition);
	glm::quat getRotation() const;
	glm::quat getAlphaRotation(const double alpha) const;
	void setRotation(glm::quat inRotation);
	glm::vec3 getScale() const;
	void setScale(glm::vec3 inScale);

	glm::vec3 getVelocity() const;
	void setVelocity(glm::vec3 inVelocity);
	glm::vec3 getAngularVelocity() const;
	void setAngularVelocity(glm::vec3 inAngularVelocity);

	glm::vec3 getForward() const;
	glm::vec3 getRight() const;
	glm::vec3 getUp() const;
	glm::vec3 getAlphaForward(const double alpha) const;
	glm::vec3 getAlphaRight(const double alpha) const;
	glm::vec3 getAlphaUp(const double alpha) const;

	friend std::ostream &operator<< (std::ostream &os, TransformComponent const &t) {
		os << "TransformComponent: ";
		os << "(" << t.position.x << ", " << t.position.y << ", " << t.position.z << "), ";
		os << "(" << t.rotation.w << ", " << t.rotation.x << ", " << t.rotation.y << ", " << t.rotation.z << "), ";
		os << "(" << t.scale.x << ", " << t.scale.y << ", " << t.scale.z << "), ";
		return os;
	}
};


#endif //BLOCKHOP_TRANSFORMCOMPONENT_H
