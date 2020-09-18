#pragma once
#include "Components.hpp"
#include "Controller.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Events/EventQueue.hpp"
#include "Objective.hpp"
#include <memory>
#include <array>
#include <map>

struct Entity
{
    using Ptr = std::unique_ptr<Entity>;

    int id = -1;
    int mask = 0;
    int flags = 0;
    bool exists = false;
};

class Scene
{
public:
    Scene();
    ~Scene();

    void update(float dt);
    void draw();

    int spawnDrone(const vec2& pos);

    int createEntity(const vec2& pos);
	void destroyEntity(int entity);

    void registerEventForEntities(int signature, Event::Type event, const EventQueue::CallbackSignature& callback);

    RigidBody* addRigidBody(int entity, RigidBody::Type type, const vec2& origin = {0,0}, const vec2& dir = {1,0});
	RigidBody* getRigidBody(int entity);

	HealthComp* addHealth(int entity, int max, int current);
	HealthComp* getHealth(int entity);

    TransformComp* getTransform(int entity);

public:
    std::array<Entity::Ptr, 1024> m_entities;

private:
    std::array<TransformComp::Ptr, 1024> m_trs;
    std::array<RigidBody::Ptr, 1024> m_rigids;
	std::array<HealthComp::Ptr, 1024> m_healths;


    std::vector<Controller::Ptr> m_controllers;

    int m_lastEntity = 0;

    PhysicsWorld m_physWorld;

    std::vector<StaticBody::Ptr> m_bobs;

    Objective::Ptr m_objective;
};