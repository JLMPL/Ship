#pragma once
#include "Controller.hpp"
#include "Physics/RigidBody.hpp"
#include <SFML/System/Clock.hpp>

class DroneController : public Controller
{
public:
    DroneController(Scene* scene, int id);
    ~DroneController() = default;

    void update(float dt) override final;

private:
    RigidBody* m_body = nullptr;
};