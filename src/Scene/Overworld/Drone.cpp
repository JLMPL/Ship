#include "Drone.hpp"
#include "Scene/Scene.hpp"
#include "Renderer.hpp"
#include "Physics/PhysicsWorld.hpp"

Drone::Drone(Scene* scene)
    : SceneObject(scene)
{
    m_body = m_scene->getPhysicsWorld()->addRigidBody({0,0}, false);
    m_body->applyLinearImpulse({1,0});

    m_player = m_scene->findObject("player_ship");
}

void Drone::update(float dt)
{
    if (m_player)
        m_body->rotateTowards(m_player->getPosition(), 100 * dt);
    else
        m_body->rotateTowards(vec2(0,0), 100 * dt);


    m_pos = m_body->getPosition();
}

void Drone::draw()
{

}
