#include "Scene.hpp"
#include "PlayerController.hpp"
#include "DroneController.hpp"
#include "PhysicsSystem.hpp"
#include "HealthSystem.hpp"
#include "Events/EventQueue.hpp"
#include "Random.hpp"

#include "ODestroyTheConvoy.hpp"

Scene::Scene()
{
    m_physicsSystem = System::Ptr(new PhysicsSystem(this));
    m_healthSystem = System::Ptr(new HealthSystem(this));

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
        if ((ent.second->mask & signature) == signature)
        {
            EventQueue::get().registerCallback(event, ent.second->id, callback);
        }
    }
}

void Scene::update(float dt)
{
    EventQueue::get().redistributeEvents();

    m_healthSystem->update();

    for (auto& controller : m_controllers)
    {
        controller->update(dt);
    }

    m_physWorld.update(dt);
    m_physicsSystem->update();

    if (m_objective->isCompleted())
    {
        // m_objective.reset(new Objective::CreateRandom());
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

    m_rigids.insert(std::make_pair(entity, RigidBody::Ptr(rigidBody)));

    auto& rig = m_rigids[entity];
    rig->setUserData(&m_entities[entity]->id);
    return rig.get();
}

RigidBody* Scene::getRigidBody(int entity)
{
    auto found = m_rigids.find(entity);

    if (found != m_rigids.end())
        return m_rigids[entity].get();
    else
        return nullptr;
}

HealthComp* Scene::addHealth(int entity, int max, int current)
{
    m_entities[entity]->mask |= (int)ComponentMask::Health;

    m_healths.insert(std::make_pair(entity, HealthComp::Ptr(new HealthComp())));

    HealthComp* hpc = m_healths[entity].get();

    hpc->maxHp = max;
    hpc->hp = current;

    static_cast<HealthSystem*>(m_healthSystem.get())->registerEntity(entity);

    return hpc;
}

HealthComp* Scene::getHealth(int entity)
{
    auto found = m_healths.find(entity);

    if (found != m_healths.end())
        return m_healths[entity].get();
    else
        return nullptr;
}

TransformComp* Scene::getTransform(int entity)
{
    return m_trs[entity].get();
}

void Scene::destroyEntity(int entity)
{
    auto& ent = m_entities[entity];
    m_trs.erase(m_trs.find(entity));

    if (ent->mask & (int)ComponentMask::RigidBody)
        m_rigids.erase(m_rigids.find(entity));

    if (ent->mask & (int)ComponentMask::Health)
        m_healths.erase(m_healths.find(entity));

    EventQueue::get().unregisterForEntity(entity);
}
