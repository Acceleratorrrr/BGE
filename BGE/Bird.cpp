#include "Bird.h"
#include "Utils.h"

using namespace BGE;

Bird::Bird()
{
}


Bird::~Bird()
{
}

void Bird::fly(float theta)
{
	if (glm::sin(theta) > 0)
	{
		left_wing->rigidBody->applyTorque(GLToBtVector(left_wing->transform->look * 3000.0f));
		right_wing->rigidBody->applyTorque(GLToBtVector(right_wing->transform->look * -3000.0f));
	}

	else
	{
		left_wing->rigidBody->applyTorque(GLToBtVector(left_wing->transform->look * -3000.0f));
		right_wing->rigidBody->applyTorque(GLToBtVector(right_wing->transform->look * 3000.0f));
	}

}

void Bird::setLeftWing(shared_ptr<PhysicsController> left_wing)
{
	this->left_wing = left_wing;
}

void Bird::setRightWing(shared_ptr<PhysicsController> right_wing)
{
	this->right_wing = right_wing;
}

void Bird::setBody(shared_ptr<PhysicsController> body)
{
	this->body = body;
}

shared_ptr<PhysicsController> Bird::getBody()
{
	return body;
}

shared_ptr<PhysicsController> Bird::getLeftWing()
{
	return left_wing;
}

shared_ptr<PhysicsController> Bird::getRightWing()
{
	return right_wing;
}
