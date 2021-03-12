#pragma once
#include "Physics/PhysicsWorld.hpp"
#include "SceneObject.hpp"
#include <memory>
#include <array>
#include <map>

class Game;

class Scene
{
public:
    using Ptr = std::unique_ptr<Scene>;

    Scene(Game* game);
    virtual ~Scene() = default;

    virtual void ready();
    void spawnAndDestroyObjects();
    virtual void update(float dt);
    virtual void draw();

	template <typename T = SceneObject>
    T* findObject(const std::string& name)
	{
		for (auto& object : m_objects)
		{
			if (object->getName() == name)
				return static_cast<T*>(object.get());
		}

		return nullptr;
	}

    template <typename T, typename... TArgs>
    T* spawnObject(TArgs... args)
    {
        m_spawnQueue.push_back(new T(this));

        T* obj = static_cast<T*>(m_spawnQueue.back());
        obj->ready(args...);

        return obj;
    }

    PhysicsWorld* getPhysicsWorld();

    void setPause(bool value);

protected:
    Game* m_game = nullptr;
    PhysicsWorld m_physicsWorld;

    std::vector<SceneObject*> m_spawnQueue;
    std::vector<SceneObject::Ptr> m_objects;

    bool m_isPaused = false;
};