#include "Scene.hpp"

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
