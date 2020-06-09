#include "DroneController.hpp"
#include "Scene.hpp"

DroneController::DroneController(Scene* scene, int id) : Controller(scene, id)
{
    m_body = m_scene->addRigidBody(m_id, RigidBody::EnemyShip);
    m_body->applyLinearImpulse({0,0});

}

void DroneController::update(float dt)
{
    auto pos = m_scene->getTransform(0)->pos;
    m_body->rotateTowards(pos, 100 * dt);

}