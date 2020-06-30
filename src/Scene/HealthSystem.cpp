#include "HealthSystem.hpp"
#include "Scene.hpp"
#include "Components.hpp"
#include "Events/EventQueue.hpp"

HealthSystem::HealthSystem(Scene* scene)
    : System(scene)
{
    m_signature = (int)ComponentMask::Health;

}

void HealthSystem::registerEntity(int id)
{
    EventQueue::get().registerCallback(Event::DamageEntity, id,
    [=](const Event& event, int entity)
    {
        HealthComp* hp = m_scene->getHealth(entity);
        hp->hp--;

        if (hp->hp < 0) hp->hp = 0;
    });
}

void HealthSystem::execute(int id)
{
    HealthComp* hc = m_scene->getHealth(id);

    if (!hc) return;

    if (hc->hp == 0 && !hc->isDead)
    {
        hc->isDead = true;

        Event evt;
        evt.type = Event::DestroyEntity;
        evt.receiver = id;

        EventQueue::get().pushEvent(evt);
    }
}
