#include "DroneController.hpp"
#include "Scene.hpp"
#include "Events/Event.hpp"

DroneController::DroneController(Scene* scene, int id) : Controller(scene, id)
{
    m_body = m_scene->addRigidBody(m_id, RigidBody::EnemyShip);
    m_body->applyLinearImpulse({0,0});
	m_scene->addHealth(m_id, 3, 3);

    m_body->setPosition({2,2});

    EventQueue::get().registerCallback(Event::DestroyEntity, m_id,
    [=](const Event& event, int ent)
    {
        m_scene->destroyEntity(ent);
    });
}

void DroneController::update(float dt)
{
    //TODO: Make controllers disappear
    if (!m_scene->getTransform(m_id)) return;

    auto playerPos = m_scene->getTransform(0)->pos;
    m_body->rotateTowards(playerPos, 100 * dt);

    auto pos = m_scene->getTransform(m_id)->pos;

    if (m_timer.getElapsedTime().asSeconds() > 1)
    {
        vec2 dir = playerPos - pos;

        int bullet = m_scene->createEntity({pos.x, pos.y});
        m_scene->addRigidBody(bullet, RigidBody::EnemyBullet, pos, math::normalize(dir));

        EventQueue::get().registerCallback(Event::DamageEntity, bullet,
        [=](const Event& event, int ent)
        {
            m_scene->destroyEntity(bullet);
        });

        m_timer.restart();
    }

}