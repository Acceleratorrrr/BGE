#pragma once
#include "PhysicsController.h"
#include "PhysicsFactory.h"
#include "GameComponent.h"
#include "Bird.h"

using namespace std;

namespace BGE {
	class BirdFactory
	{
	public:
		BirdFactory(btDiscreteDynamicsWorld * dynamicsWorld);
		~BirdFactory();

		shared_ptr<PhysicsController> CreateBody(glm::vec3 position, glm::quat orientation);

		void CreateWings(shared_ptr<PhysicsController> body, glm::vec3 position, glm::quat orientation);
		void CreateLegs(shared_ptr<PhysicsController> body, glm::vec3 position, glm::quat orientation);
		void CreateEyes(shared_ptr<PhysicsController> body, glm::vec3 position, glm::quat orientation);

		shared_ptr<Bird> BirdFactory::CreateBird(glm::vec3 position, glm::quat orientation);


	private:
		btDiscreteDynamicsWorld * dynamicsWorld;
		shared_ptr<PhysicsFactory> physicsFactory;

		shared_ptr<Bird> bird;

	};
}