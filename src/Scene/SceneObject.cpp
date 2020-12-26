#include "SceneObject.hpp"

const vec2& SceneObject::getPosition() const
{
    return m_pos;
}

const std::string& SceneObject::getName() const
{
    return m_name;
}

void SceneObject::destory()
{
    m_destroyed = true;
}

bool SceneObject::isDestroyed()
{
    return m_destroyed;
}
