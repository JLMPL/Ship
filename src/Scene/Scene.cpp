#include "Scene.hpp"
#include "PlayerController.hpp"
#include "Events/EventQueue.hpp"

Scene::Scene()
{
    int player = createEntity({0,0});
    m_controllers.emplace_back(new PlayerController(this, player));
}

Scene::~Scene()
{
}

void Scene::update(float dt)
{
    EventQueue::get().redistributeEvents();

    for (auto& controller : m_controllers)
    {
        controller->update(dt);
    }

    m_physWorld.update(dt);
}

void Scene::draw()
{
    m_physWorld.draw();
}

int Scene::createEntity(const vec2& pos)
{
    Entity::Ptr ent(new Entity());
    ent->id = m_lastEntity;
    ent->mask = (int)ComponentMask::Transform;
    m_entities.insert(std::make_pair(m_lastEntity, std::move(ent)));

    m_trs.insert(std::make_pair(m_lastEntity, TransformComp::Ptr(new TransformComp())));

    m_lastEntity++;
    return m_lastEntity-1;
}

RigidBody* Scene::addRigidBody(int entity, RigidBody::Type type, const vec2& origin, const vec2& dir)
{
    m_entities[entity]->mask |= (int)ComponentMask::RigidBody;

    RigidBody* rigidBody = nullptr;

    if (type == RigidBody::PlayerShip || type == RigidBody::EnemyShip)
        rigidBody = m_physWorld.addRigidBody({0,0}, type == RigidBody::PlayerShip);
    else if (type == RigidBody::PlayerBullet || type == RigidBody::EnemyBullet)
        rigidBody = m_physWorld.spawnBullet(origin, dir, type == RigidBody::PlayerBullet);

    m_rigids.insert(std::make_pair(entity, RigidBodyComp::Ptr(new RigidBodyComp(rigidBody))));

    auto& rig = m_rigids[entity]->rb;
    rig->setUserData(&m_entities[entity]->id);
    return rig;
}

void Scene::destroyEntity(int entity) const
{
    printf("Scene::destroyEntity %d\n", entity);
}
