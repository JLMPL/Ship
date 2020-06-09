#pragma once
#include "Components.hpp"
#include "Controller.hpp"
#include "Physics/PhysicsWorld.hpp"
#include <memory>
#include <map>

struct Entity
{
    using Ptr = std::unique_ptr<Entity>;

    int id = -1;
    int mask = 0;
    int flags = 0;
};

class Scene
{
public:
    Scene();
    ~Scene();

    void update(float dt);
    void draw();

    int createEntity(const vec2& pos);
    RigidBody* addRigidBody(int entity, RigidBody::Type type, const vec2& origin = {0,0}, const vec2& dir = {1,0});

    void destroyEntity(int entity) const;

private:
    std::map<int, Entity::Ptr> m_entities;
    std::map<int, TransformComp::Ptr> m_trs;
    std::map<int, RigidBodyComp::Ptr> m_rigids;

    std::vector<Controller::Ptr> m_controllers;

    int m_lastEntity = 0;

    PhysicsWorld m_physWorld;
};