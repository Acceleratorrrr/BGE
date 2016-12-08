#pragma once
#include "PhysicsController.h"

using namespace std;

namespace BGE
{
	class Bird
	{
	public:
		Bird();
		~Bird();

		void fly(float theta);

		void setLeftWing(shared_ptr<PhysicsController> left_wing);
		void setRightWing(shared_ptr<PhysicsController> right_wing);
		void setBody(shared_ptr<PhysicsController> body);

		shared_ptr<PhysicsController> getBody();
		shared_ptr<PhysicsController> getLeftWing();
		shared_ptr<PhysicsController> getRightWing();

	private:
		shared_ptr<PhysicsController> left_wing;
		shared_ptr<PhysicsController> right_wing;
		shared_ptr<PhysicsController> body;
	};
}

