#pragma once
#include "Physics/PhysicsWorld.hpp"
#include "SceneObject.hpp"
#include <memory>
#include <array>
#include <map>

class Scene
{
public:
    Scene();
    ~Scene() = default;

    void ready();
    void spawnAndDestroyObjects();
    void update(float dt);
    void draw();

    SceneObject* findObject(const std::string& name);

    template <typename T, typename... TArgs>
    T* spawnObject(TArgs... args)
    {
        m_spawnQueue.push_back(new T(this));

        T* obj = static_cast<T*>(m_spawnQueue.back());
        obj->ready(args...);

        return obj;
    }

    PhysicsWorld* getPhysicsWorld();

private:
    std::vector<SceneObject*> m_spawnQueue;
    std::vector<SceneObject::Ptr> m_objects;
    PhysicsWorld m_physicsWorld;
};