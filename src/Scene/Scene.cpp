#include "Scene.hpp"
#include "Random.hpp"

#include "Overworld/Drone.hpp"
#include "Overworld/Player.hpp"
#include "Overworld/Hud.hpp"
#include "StarBackground.hpp"

Scene::Scene()
{
    m_context.physWorld = &m_physWorld;

    for (int i = 0; i < 1000; i++)
    {
        m_physWorld.addStaticBody({rando::inRange(-1000.f, 1000.f), rando::inRange(-1000.f, 1000.f)}, rando::inRange(2.f, 5.f));
    }

    m_objects.emplace_back(new StarBackground(&m_context));
    m_objects.emplace_back(new Player(&m_context));
    m_objects.emplace_back(new Drone(&m_context));
    m_objects.emplace_back(new Hud(&m_context));
}

Scene::~Scene()
{
}

void Scene::update(float dt)
{
    for (auto& ent : m_objects)
        ent->update(dt);

    m_physWorld.update(dt);
}

void Scene::draw()
{
    for (auto& ent : m_objects)
        ent->draw();

    m_physWorld.draw();
}
