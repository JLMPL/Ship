#pragma once
#include "Physics/PhysicsWorld.hpp"
#include "Entity.hpp"
#include <memory>
#include <array>
#include <map>

struct SceneContext
{
    Entity* playerShip = nullptr;
    PhysicsWorld* physWorld = nullptr;
};

enum SpacecraftType
{
    SCRAFT_PLAYER,
    SCRAFT_DRONE,
    SCRAFT_COUNT
};

struct Spacecraft
{
    SpacecraftType type = SCRAFT_COUNT;
    SceneContext* sceneCtx = nullptr;
    RigidBody* body = nullptr;
    vec2 pos;

    int health = 1;
    int maxHealth = 1;
};

void initPlayer(Spacecraft* craft);
void updatePlayer(Spacecraft* craft);
void drawPlayer(Spacecraft* craft);

class Scene
{
public:
    Scene();
    ~Scene();

    void update(float dt);
    void draw();

private:
    std::vector<Entity::Ptr> m_entities;
    int m_lastEntity = 0;

    PhysicsWorld m_physWorld;

    SceneContext m_context;

    Spacecraft m_player;

};