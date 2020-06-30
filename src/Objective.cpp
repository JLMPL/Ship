#include "Objective.hpp"

Objective::Objective(Scene* scene)
    : m_scene(scene)
{
}

bool Objective::isCompleted() const
{
    return m_completed;
}
