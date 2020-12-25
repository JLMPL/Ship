#pragma once
#include "Physics/PhysicsWorld.hpp"
#include "SceneObject.hpp"
#include <memory>
#include <array>
#include <map>

struct SceneContext
{
    PhysicsWorld* physWorld = nullptr;
};

class Scene
{
public:
    Scene();
    ~Scene();

    void update(float dt);
    void draw();

private:
    std::vector<SceneObject::Ptr> m_objects;
    int m_lastEntity = 0;

    PhysicsWorld m_physWorld;

    SceneContext m_context;
};