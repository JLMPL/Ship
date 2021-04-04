#include "Scene.hpp"
#include "SceneObject.hpp"
#include "Game.hpp"

Scene::Scene(Game* game)
 : m_game(game)
{
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
    {
        if (!m_isPaused)
        {
            ent->update(dt);
        }
        if (m_isPaused && !ent->isPausable())
        {
            ent->update(dt);
        }
    }

    if (!m_isPaused)
        m_physicsWorld.update(dt);
}

void Scene::draw()
{
    for (auto& ent : m_objects)
        ent->draw();

    m_physicsWorld.draw();
}

std::vector<SceneObject*> Scene::findObjectsInRange(const vec2& pos, float range)
{
    std::vector<SceneObject*> found;

    for (auto& object : m_objects)
    {
        if (math::distance(object->getPosition(), pos) <= range)
        {
            found.push_back(object.get());
        }
    }

    return found;
}

int Scene::countObjectsByName(const std::string& name)
{
    int count = 0;

    for (auto& object : m_objects)
    {
        if (object->getName() == name)
            count++;
    }

    return count;
}

PhysicsWorld* Scene::getPhysicsWorld()
{
    return &m_physicsWorld;
}

void Scene::setPause(bool value)
{
    m_isPaused = value;
}
