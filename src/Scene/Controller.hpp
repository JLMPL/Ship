#pragma once
#include <memory>

class Scene;

class Controller
{
public:
    using Ptr = std::unique_ptr<Controller>;

    Controller(Scene* scene, int id) :
        m_scene(scene), m_id(id)
    {}
    virtual ~Controller() {}

    virtual void update(float dt) = 0;

protected:
    Scene* m_scene = nullptr;
    int m_id = -1;
};