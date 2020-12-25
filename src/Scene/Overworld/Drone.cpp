#include "Drone.hpp"
#include "Scene/Scene.hpp"
#include "Renderer.hpp"
#include "Physics/PhysicsWorld.hpp"

Drone::Drone(SceneContext* context)
    : SceneObject(context)
{
    m_body = m_sContext->physWorld->addRigidBody({0,0}, false);

    m_body->applyLinearImpulse({1,0});
}

void Drone::update(float dt)
{
    // if (m_sContext->playerShip)
        // m_body->rotateTowards(m_sContext->playerShip->getPosition(), 100 * dt);
    // else
        m_body->rotateTowards(vec2(0,0), 100 * dt);


    m_pos = m_body->getPosition();
}

void Drone::draw()
{

}
