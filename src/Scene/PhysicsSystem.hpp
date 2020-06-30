#pragma once
#include "System.hpp"

class PhysicsSystem : public System
{
public:
	PhysicsSystem(Scene* scene);

	void execute(int id) override final;
};