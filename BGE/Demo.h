#pragma once
#include "Game.h"
#include "GameComponent.h"
#include "BirdFactory.h"

using namespace BGE;

namespace BGE {
	class Demo : 
		public Game
	{
	public:
		Demo();
		~Demo();

		bool Initialise();
		void Update(float timeDelta);

		void UpdateCamera();

		const glm::vec3 grivity = glm::vec3(0, -9.8f, 0);

		shared_ptr<BirdFactory> birdFactory;

		shared_ptr<Bird> bird;
		shared_ptr<PhysicsController> body;

		float theta = 0.0f;
	};
}

