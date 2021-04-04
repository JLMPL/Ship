#pragma once
#include "Physics/PhysicsWorld.hpp"
#include "SceneObject.hpp"
#include <memory>
#include <array>
#include <map>
#include <limits>

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

        printf("%s - not found in scene!\n", name.c_str());
		return nullptr;
	}

    std::vector<SceneObject*> findObjectsInRange(const vec2& pos, float range);

    template <typename T = SceneObject>
    T* findClosestObjectByName(const vec2& pos, const std::string& name = "[ignore]")
    {
        SceneObject* closest = nullptr;
        float closestDistance = 1000.f;

        for (auto& object : m_objects)
        {
            float dist = math::distance(object->getPosition(), pos);

            bool nameMatch = object->getName() == name;

            if (name == "[ignore]")
                nameMatch = true;

            if (nameMatch && dist < closestDistance)
            {
                closest = object.get();
                closestDistance = dist;
            }
        }

        return closest;
    }

    template <typename T = SceneObject>
    T* findClosestObjectByNames(const vec2& pos, const std::vector<std::string>& names)
    {
        SceneObject* closest = nullptr;
        float closestDistance = 1000.f;

        for (auto& object : m_objects)
        {
            float dist = math::distance(object->getPosition(), pos);

            bool nameMatch = false;

            for (auto& name : names)
            {
                if (name == object->getName())
                {
                    nameMatch = true;
                    break;
                }
            }

            if (nameMatch && dist < closestDistance)
            {
                closest = object.get();
                closestDistance = dist;
            }
        }

        return closest;
    }

    int countObjectsByName(const std::string& name);

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