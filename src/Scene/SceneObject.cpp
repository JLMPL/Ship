#include "SceneObject.hpp"

void SceneObject::setPosition(const vec2& pos)
{
    m_pos = pos;
}

const vec2& SceneObject::getPosition() const
{
    return m_pos;
}

const std::string& SceneObject::getName() const
{
    return m_name;
}

void SceneObject::destroy()
{
    m_destroyed = true;
}

bool SceneObject::isDestroyed()
{
    return m_destroyed;
}
