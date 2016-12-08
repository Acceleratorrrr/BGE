#include "Demo.h"
#include "Utils.h"
#include "VectorDrawer.h"

using namespace BGE;

Demo::Demo()
{
	;
}

Demo::~Demo()
{
	;
}

bool Demo::Initialise()
{
	// Create Ground
	physicsFactory->CreateGroundPhysics();

	//set gravity
	dynamicsWorld->setGravity(GLToBtVector(grivity));

	birdFactory = make_shared<BirdFactory>(dynamicsWorld);

	bird = birdFactory->CreateBird(glm::vec3(0.0f, 20.0f, 0.0f), glm::quat());
	body = bird->getBody();

	Game::Initialise();

	//UpdateCamera();

	return true;
}

void Demo::Update(float timeDelta)
{
	theta += timeDelta * 2.5f;

	const Uint8 * keyState = Game::Instance()->GetKeyState();

	if (keyState[SDL_SCANCODE_UP])
	{
		body->rigidBody->applyForce(GLToBtVector(body->transform->look * 1000.0f), GLToBtVector(glm::vec3(10.0f, 0.0f, 0.0f)));
	}

	if (keyState[SDL_SCANCODE_DOWN])
	{
		body->rigidBody->applyForce(GLToBtVector(body->transform->look * -1000.0f), GLToBtVector(glm::vec3(-10.0f, 0.0f, 0.0f)));
	}

	if (keyState[SDL_SCANCODE_LEFT])
	{
		body->rigidBody->applyTorque(GLToBtVector(body->transform->up * 10000.0f));
	}

	if (keyState[SDL_SCANCODE_RIGHT])
	{
		body->rigidBody->applyTorque(GLToBtVector(body->transform->up * -10000.0f));
	}

	if (keyState[SDL_SCANCODE_U])
	{
		//body->rigidBody->applyForce(GLToBtVector(body->transform->up * 1000.0f), GLToBtVector(glm::vec3(0.0f, 0.0f, 0.0f)));
		body->rigidBody->applyTorque(GLToBtVector(body->transform->right * -10000.0f));
	}

	if (keyState[SDL_SCANCODE_J])
	{
		//body->rigidBody->applyForce(GLToBtVector(body->transform->up * -2000.0f), GLToBtVector(glm::vec3(0.0f, 0.0f, 0.0f)));
		body->rigidBody->applyTorque(GLToBtVector(body->transform->right * 10000.0f));
	}

	if (keyState[SDL_SCANCODE_H])
	{
		body->rigidBody->applyTorque(GLToBtVector(body->transform->look * -3000.0f));
	}

	if (keyState[SDL_SCANCODE_K])
	{
		body->rigidBody->applyTorque(GLToBtVector(body->transform->look * 3000.0f));
	}

	if (keyState[SDL_SCANCODE_SPACE]) {
		body->rigidBody->applyForce(GLToBtVector(glm::vec3(0.0f, 1.0f, 0.0f) * 2000.0f), GLToBtVector(glm::vec3(0.0f, 10.0f, 0.0f)));
	}

	//bird->rigidBody->applyForce(GLToBtVector(bird->transform->up * 300.0f * glm::sin(theta)), GLToBtVector(glm::vec3(0.0f, 0.0f, 0.0f)));

	bird->fly(theta);
	
	//UpdateCamera();

	Game::Update(timeDelta);
}

void Demo::UpdateCamera() {
	camera->transform->position = body->transform->position + body->transform->look * (-60.0f) + glm::vec3(0, 5.0f, 0);
	camera->transform->orientation = body->transform->orientation;
}
