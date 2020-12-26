#include "SceneObject.hpp"

const vec2& SceneObject::getPosition() const
{
    return m_pos;
}

const std::string& SceneObject::getName() const
{
    return m_name;
}