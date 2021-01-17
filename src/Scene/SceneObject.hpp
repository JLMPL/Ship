#pragma once
#include "Core/Math.hpp"
#include <memory>

struct Scene;

class SceneObject
{
public:
    using Ptr = std::unique_ptr<SceneObject>;

    template <typename T>
    T* as()
    {
        return static_cast<T*>(this);
    }

    SceneObject(Scene* context)
     : m_scene(context) {}
    virtual ~SceneObject() {};

    virtual void ready() {}

    virtual void update(float dt) = 0;
    virtual void draw() = 0;

    virtual void onContact(SceneObject* other) {}

    virtual void setPosition(const vec2& pos);

    const vec2& getPosition() const;
    const std::string& getName() const;

    void destroy();
    bool isDestroyed() const;

    bool isPausable() const;

protected:
    Scene* m_scene = nullptr;
    vec2 m_pos;

    bool m_destroyed = false;
    bool m_pausable = true;

    std::string m_name = "[blank]";
};

