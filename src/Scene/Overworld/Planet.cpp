#include "Planet.hpp"
#include "Scene/Scene.hpp"
#include "Renderer.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Random.hpp"

Planet::Planet(Scene* scene)
    : SceneObject(scene)
{
    float radius = rng::inRange(2.f, 5.f);
    m_body = m_scene->getPhysicsWorld()->addStaticBody({
        rng::inRange(-1000.f, 1000.f),
        rng::inRange(-1000.f, 1000.f)},
        radius);

    m_name = "planet";
    m_mesh.loadFromFile("data/meshes/planet.obj");
    m_mesh.setPosition(m_body->getPosition());
    m_mesh.setScale(radius);
}

void Planet::ready(const vec2& spawnPoint)
{
}

void Planet::update(float dt)
{
}

void Planet::draw()
{
    m_mesh.draw();
}
