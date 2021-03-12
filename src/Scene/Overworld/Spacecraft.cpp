#include "Spacecraft.hpp"
#include "../Scene.hpp"

Spacecraft::Spacecraft(Scene* scene)
 : SceneObject(scene)
{
	m_thruster.setVisible(true);
}

void Spacecraft::ready(bool player)
{
    m_body = m_scene->getPhysicsWorld()->addRigidBody({0,0}, player);
    m_body->setUserData(this);
}

void Spacecraft::update(float dt)
{
    m_trail.setPosition(m_pos);
    m_trail.update();
	m_thruster.update();

	m_thruster.setTransform(m_pos, m_body->getAngle() + M_PI / 2, 0.8f);
}

void Spacecraft::draw()
{
    m_mesh.setPosition(m_pos);
    m_mesh.setOffset(vec2(0, 0.2));
    m_mesh.setRotation(m_body->getAngle() + M_PI/2);
    m_mesh.setScale(0.7f);

    m_trail.draw();
	m_thruster.draw();
    m_mesh.draw();
	m_thruster.setVisible(false);
}

void Spacecraft::setPosition(const vec2& pos)
{
    m_body->setPosition(pos);
}

void Spacecraft::thrust(const vec2& dir)
{
	m_thruster.setVisible(true);
	m_body->applyLinearImpulse(dir);
	m_thruster.setLength(math::length(dir) * 20);
}