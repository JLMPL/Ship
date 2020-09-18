#include "Scene.hpp"
#include "Controllers/PlayerController.hpp"
#include "Controllers/DroneController.hpp"
#include "Events/EventQueue.hpp"
#include "Random.hpp"
#include "Scene/Systems.hpp"

#include "ODestroyTheConvoy.hpp"

Scene::Scene()
{
    for (auto& i : m_entities)
        i.reset(nullptr);

    for (auto& i : m_trs)
        i.reset(nullptr);

    for (auto& i : m_rigids)
        i.reset(nullptr);

    for (auto& i : m_healths)
        i.reset(nullptr);

    int player = createEntity({0,0});
    m_controllers.emplace_back(new PlayerController(this, player));

    for (int i = 0; i < 1000; i++)
    {
        auto body = m_physWorld.addStaticBody({rando::inRange(-1000.f, 1000.f), rando::inRange(-1000.f, 1000.f)}, rando::inRange(2.f, 5.f));
        m_bobs.emplace_back(body);
    }

    m_objective = Objective::Ptr(new ODestroyTheConvoy(this));
}

Scene::~Scene()
{
}

int Scene::spawnDrone(const vec2& pos)
{
    int drone = createEntity({0,0});
    m_controllers.emplace_back(new DroneController(this, drone));

    getRigidBody(drone)->setPosition(pos);
    return drone;
}

void Scene::registerEventForEntities(int signature, Event::Type event, const EventQueue::CallbackSignature& callback)
{
    for (auto& ent : m_entities)
    {
        if (!ent) continue;
        if ((ent->mask & signature) == signature)
        {
            EventQueue::get().registerCallback(event, ent->id, callback);
        }
    }
}

void Scene::update(float dt)
{
    EventQueue::get().redistributeEvents();

    m_controllers.erase(std::remove_if(m_controllers.begin(), m_controllers.end(),
    [](const Controller::Ptr& ctrl)
    {
        return ctrl->isDestroyed();
    }), m_controllers.end());

    healthSystemUpdate(this);

    for (auto& controller : m_controllers)
    {
        controller->update(dt);
    }

    m_physWorld.update(dt);
    physicsSystemUpdate(this);

    m_objective->check();
    if (m_objective->isCompleted())
    {
        m_objective.reset(new ODestroyTheConvoy(this));
        printf("Objective completed!\n");
    }
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
    m_entities[m_lastEntity] = std::move(ent);

    m_trs[m_lastEntity] = TransformComp::Ptr(new TransformComp());

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

    m_rigids[entity] = RigidBody::Ptr(rigidBody);

    auto& rig = m_rigids[entity];
    rig->setUserData(&m_entities[entity]->id);
    return rig.get();
}

RigidBody* Scene::getRigidBody(int entity)
{
    return (m_rigids[entity]) ? m_rigids[entity].get() : nullptr;
}

HealthComp* Scene::addHealth(int entity, int max, int current)
{
    m_entities[entity]->mask |= (int)ComponentMask::Health;

    m_healths[entity] = HealthComp::Ptr(new HealthComp());

    HealthComp* hpc = m_healths[entity].get();

    hpc->maxHp = max;
    hpc->hp = current;

    healthSystemRegisterEntity(this, entity);

    return hpc;
}

HealthComp* Scene::getHealth(int entity)
{
    return (m_healths[entity]) ? m_healths[entity].get() : nullptr;
}

TransformComp* Scene::getTransform(int entity)
{
    return m_trs[entity].get();
}

void Scene::destroyEntity(int entity)
{
    if (!m_entities[entity]) return;

    m_entities[entity].reset(nullptr);
    m_trs[entity].reset(nullptr);
    m_rigids[entity].reset(nullptr);
    m_healths[entity].reset(nullptr);

    //TODO: Clear those somehow
    EventQueue::get().unregisterForEntity(entity);
}
