#include "Controller.hpp"
#include "Scene.hpp"

bool Controller::isDestroyed() const
{
    if (m_id == -1) return false;

    if (!m_scene->getTransform(m_id)) return true;

    return false;
}