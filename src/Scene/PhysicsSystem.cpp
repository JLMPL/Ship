#include "PhysicsSystem.hpp"
#include "Scene.hpp"

PhysicsSystem::PhysicsSystem(Scene* scene)
	: System(scene)
{
	m_signature = (int)ComponentMask::RigidBody;
}

void PhysicsSystem::execute(int id)
{
	RigidBody* rb = m_scene->getRigidBody(id);
	TransformComp* tr = m_scene->getTransform(id);

    if (!rb) return;

	tr->pos = rb->getPosition();
}
