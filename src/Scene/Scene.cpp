#include "Scene.hpp"
#include "Random.hpp"

#include "Drone.hpp"

Scene::Scene()
{

    m_context.physWorld = &m_physWorld;

    for (int i = 0; i < 1000; i++)
    {
        m_physWorld.addStaticBody({rando::inRange(-1000.f, 1000.f), rando::inRange(-1000.f, 1000.f)}, rando::inRange(2.f, 5.f));
    }

    m_entities.emplace_back(new Drone(&m_context));

    m_player.sceneCtx = &m_context;
    initPlayer(&m_player);
}

Scene::~Scene()
{
}

void Scene::update(float dt)
{
    for (auto& ent : m_entities)
        ent->update(dt);

    updatePlayer(&m_player);

    m_physWorld.update(dt);
}

void Scene::draw()
{
    for (auto& ent : m_entities)
        ent->draw();

    drawPlayer(&m_player);

    m_physWorld.draw();
}
