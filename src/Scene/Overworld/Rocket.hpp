#pragma once
#include "Scene/SceneObject.hpp"

class Rocket : public SceneObject
{
public:
	Rocket(Scene* scene);
	~Rocket() = default;

	void ready(const vec2& pos, const vec2& dir);
	void update(float dt) override final;
	void draw() override final;

private:
	
};