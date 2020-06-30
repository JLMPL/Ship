#pragma once
#include <memory>

class Scene;

class System
{
public:
	using Ptr = std::unique_ptr<System>;

	System(Scene* scene);
	virtual ~System() {}

	void update();

protected:
	virtual void execute(int id) = 0;

protected:
	Scene* m_scene = nullptr;
	int m_signature = 0;
};