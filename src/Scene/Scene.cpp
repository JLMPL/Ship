#include "Scene.hpp"
#include "Random.hpp"

#include "Overworld/Drone.hpp"
#include "Overworld/Player.hpp"
#include "Overworld/Hud.hpp"
#include "StarBackground.hpp"

Scene::Scene()
{
    for (int i = 0; i < 1000; i++)
    {
        m_planets.push_back(m_physicsWorld.addStaticBody({
            rando::inRange(-1000.f, 1000.f),
            rando::inRange(-1000.f, 1000.f)},
            rando::inRange(2.f, 5.f)));
    }

    m_objects.emplace_back(new StarBackground(this));
    m_objects.emplace_back(new Player(this));
    m_objects.emplace_back(new Drone(this));
    m_objects.emplace_back(new Hud(this));

    ready();
}

void Scene::ready()
{
    for (auto& object : m_objects)
        object->ready();
}

void Scene::spawnAndDestroyObjects()
{
    for (auto i = m_objects.begin(); i != m_objects.end();)
    {
        if ((*i)->isDestroyed())
            i = m_objects.erase(i);
        else
            i++;
    }

    for (auto& obj : m_spawnQueue)
    {
        m_objects.emplace_back(obj);
    }
    m_spawnQueue.clear();
}

void Scene::update(float dt)
{
    spawnAndDestroyObjects();

    for (auto& ent : m_objects)
        ent->update(dt);

    m_physicsWorld.update(dt);
}

void Scene::draw()
{
    for (auto& ent : m_objects)
        ent->draw();

    m_physicsWorld.draw();
}

SceneObject* Scene::findObject(const std::string& name)
{
    for (auto& object : m_objects)
    {
        if (object->getName() == name)
            return object.get();
    }

    return nullptr;
}

PhysicsWorld* Scene::getPhysicsWorld()
{
    return &m_physicsWorld;
}
