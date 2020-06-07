#include "Scene.hpp"
#include "PlayerController.hpp"

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
    ent->mask = (int)ComponentMask::Transform;
    m_entities.insert(std::make_pair(m_lastEntity, std::move(ent)));

    m_trs.insert(std::make_pair(m_lastEntity, TransformComp::Ptr(new TransformComp())));

    m_lastEntity++;
    return m_lastEntity-1;
}

RigidBody* Scene::addRigidBody(int entity, bool isPlayer)
{
    m_entities[entity]->mask |= (int)ComponentMask::RigidBody;

    auto rigidBody = m_physWorld.addRigidBody({0,0}, isPlayer);
    m_rigids.insert(std::make_pair(entity, RigidBodyComp::Ptr(new RigidBodyComp(rigidBody))));

    return m_rigids[entity]->rb;
}
