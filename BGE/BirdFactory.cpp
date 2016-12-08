#include "BirdFactory.h"
#include "Utils.h"
#include "VectorDrawer.h"

using namespace BGE;

BirdFactory::BirdFactory(btDiscreteDynamicsWorld * dynamicsWorld)
{
	this->dynamicsWorld = dynamicsWorld;
	this->physicsFactory = make_shared<PhysicsFactory>(dynamicsWorld);

	bird = make_shared<Bird>();
}


BirdFactory::~BirdFactory()
{
}

shared_ptr<Bird> BirdFactory::CreateBird(glm::vec3 position, glm::quat orientation) {
	shared_ptr<PhysicsController> body = CreateBody(position, orientation);

	CreateWings(body, position, orientation);
	CreateLegs(body, position, orientation);
	CreateEyes(body, position, orientation);

	return bird;
}

shared_ptr<PhysicsController> BirdFactory::CreateBody(glm::vec3 position, glm::quat orientation)
{
	shared_ptr<PhysicsController> body = physicsFactory->CreateBox(10.0f, 10.0f, 10.0f, position + glm::vec3(0.0f, 7.0f, 0.0f), orientation, false, true);

	body->Attach(make_shared<VectorDrawer>());

	bird->setBody(body);

	return body;
}

void BirdFactory::CreateWings(shared_ptr<PhysicsController> body, glm::vec3 position, glm::quat orientation) {

	shared_ptr<PhysicsController> left_wing = physicsFactory->CreateBox(20.0f, 1.0f, 20.0f, position + glm::vec3(-18.0f, 7.0f, 0.0f), orientation, false, true);

	btHingeConstraint * left_wing_hinge = new btHingeConstraint(*body->rigidBody, *left_wing->rigidBody, btVector3(0.0f, 0.0f, 0.0f), btVector3(18.0f, 0.0f, 0), GLToBtVector(body->transform->look), GLToBtVector(left_wing->transform->look), true);
	left_wing_hinge->setLimit(-glm::pi<float>() / 5.0f, glm::pi<float>() / 5.0f);
	dynamicsWorld->addConstraint(left_wing_hinge);

	shared_ptr<PhysicsController> right_wing = physicsFactory->CreateBox(20.0f, 1.0f, 20.0f, position + glm::vec3(18.0f, 7.0f, 0.0f), orientation, false, true);

	btHingeConstraint * right_wing_hinge = new btHingeConstraint(*body->rigidBody, *right_wing->rigidBody, btVector3(0.0f, 0.0f, 0.0f), btVector3(-18.0f, 0.0f, 0), GLToBtVector(body->transform->look), GLToBtVector(right_wing->transform->look), true);
	right_wing_hinge->setLimit(-glm::pi<float>() / 5.0f, glm::pi<float>() / 5.0f);
	dynamicsWorld->addConstraint(right_wing_hinge);

	bird->setLeftWing(left_wing);
	bird->setRightWing(right_wing);
}

void BirdFactory::CreateLegs(shared_ptr<PhysicsController> body, glm::vec3 position, glm::quat orientation)
{
	shared_ptr<PhysicsController> left_leg = physicsFactory->CreateBox(4.0f, 2.0f, 8.0f, position + glm::vec3(-3.0f, 0.0f, 0.0f), orientation, false, true);

	shared_ptr<PhysicsController> right_leg = physicsFactory->CreateBox(4.0f, 2.0f, 8.0f, position + glm::vec3(3.0f, 0.0f, 0.0f), orientation, false, true);

}

void BirdFactory::CreateEyes(shared_ptr<PhysicsController> body, glm::vec3 position, glm::quat orientation)
{
	shared_ptr<PhysicsController> left_eye = physicsFactory->CreateSphere(2.5f, position + glm::vec3(-2.5f, 7.0f, -7.5f), orientation, false, true);

	btPoint2PointConstraint * left_eye_point = new btPoint2PointConstraint(*body->rigidBody, *left_eye->rigidBody, GLToBtVector(glm::vec3(-2.5f, 0.0f, -5.0f)), GLToBtVector(glm::vec3(-2.5f, 0.0f, 0.0f)));
	dynamicsWorld->addConstraint(left_eye_point);

	shared_ptr<PhysicsController> right_eye = physicsFactory->CreateSphere(2.5f, position + glm::vec3(2.5f, 7.0f, -7.5f), orientation, false, true);

	btPoint2PointConstraint * right_eye_point = new btPoint2PointConstraint(*body->rigidBody, *right_eye->rigidBody, GLToBtVector(glm::vec3(2.5f, 0.0f, -5.0f)), GLToBtVector(glm::vec3(-2.5f, 0.0f, 0.0f)));
	dynamicsWorld->addConstraint(right_eye_point);

	shared_ptr<PhysicsController> left_eye_2 = physicsFactory->CreateSphere(2.5f, position + glm::vec3(-2.5f, 7.0f, 7.5f), orientation, false, true);

	btPoint2PointConstraint * left_eye_point_2 = new btPoint2PointConstraint(*body->rigidBody, *left_eye_2->rigidBody, GLToBtVector(glm::vec3(-2.5f, 0.0f, 5.0f)), GLToBtVector(glm::vec3(2.5f, 0.0f, 0.0f)));
	dynamicsWorld->addConstraint(left_eye_point_2);

	shared_ptr<PhysicsController> right_eye_2 = physicsFactory->CreateSphere(2.5f, position + glm::vec3(2.5f, 7.0f, 7.5f), orientation, false, true);

	btPoint2PointConstraint * right_eye_point_2 = new btPoint2PointConstraint(*body->rigidBody, *right_eye_2->rigidBody, GLToBtVector(glm::vec3(2.5f, 0.0f, 5.0f)), GLToBtVector(glm::vec3(2.5f, 0.0f, 0.0f)));
	dynamicsWorld->addConstraint(right_eye_point_2);
}
