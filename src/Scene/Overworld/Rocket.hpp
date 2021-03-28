#pragma once
#include "Scene/SceneObject.hpp"
#include <SFML/System/Time.hpp>
#include "Visual/Trail.hpp"
#include "Visual/Mesh.hpp"

class Rocket : public SceneObject
{
public:
	Rocket(Scene* scene);
	~Rocket() = default;

	void ready(const vec2& pos, const vec2& dir);
	void update(float dt) override final;
	void draw() override final;

private:
    vec2 m_dir;
    float m_acceleration = 50.f;
    bool m_attacking = false;

    SceneObject* m_target = nullptr;
    sf::Time m_timer;

    Trail m_trail;
    Mesh m_mesh;
};