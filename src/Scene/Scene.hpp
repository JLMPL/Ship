#pragma once
#include "Components.hpp"
#include "Controller.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "System.hpp"
#include "Events/EventQueue.hpp"
#include "Objective.hpp"
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

    int spawnDrone(const vec2& pos);

    int createEntity(const vec2& pos);
	void destroyEntity(int entity);

    void registerEventForEntities(int signature, Event::Type event, const EventQueue::CallbackSignature& callback);

    RigidBody* addRigidBody(int entity, RigidBody::Type type, const vec2& origin = {0,0}, const vec2& dir = {1,0});
	RigidBody* getRigidBody(int entity);

	HealthComp* addHealth(int entity, int max, int current);
	HealthComp* getHealth(int entity);

    TransformComp* getTransform(int entity);

private:
    std::map<int, Entity::Ptr> m_entities;
    std::map<int, TransformComp::Ptr> m_trs;
    std::map<int, RigidBody::Ptr> m_rigids;
	std::map<int, HealthComp::Ptr> m_healths;

    std::vector<Controller::Ptr> m_controllers;

    int m_lastEntity = 0;

    PhysicsWorld m_physWorld;
	System::Ptr m_physicsSystem;
    System::Ptr m_healthSystem;

    std::vector<StaticBody::Ptr> m_bobs;

    Objective::Ptr m_objective;

	friend class System;
};