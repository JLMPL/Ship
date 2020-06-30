#include "ODestroyTheConvoy.hpp"
#include "Scene/Scene.hpp"
#include "Events/EventQueue.hpp"
#include "Random.hpp"

ODestroyTheConvoy::ODestroyTheConvoy(Scene* scene)
    : Objective(scene)
{
    m_dronesToKill = rando::inRangei(2, 5);

    for (int i = 0; i < m_dronesToKill; i++)
    {
        int drone = m_scene->spawnDrone({4.f + i * 3.f, 0.f});

        EventQueue::get().registerCallback(Event::DestroyEntity, drone,
        [&](const Event& event, int ent)
        {
            m_dronesKilled++;
        });
    }
}

void ODestroyTheConvoy::check()
{
    if (m_dronesKilled == m_dronesToKill)
    {
        m_completed = true;
    }
}