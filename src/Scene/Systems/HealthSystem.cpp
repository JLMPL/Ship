#include "Scene/Systems.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Components.hpp"
#include "Events/EventQueue.hpp"

static constexpr int signature = (int)ComponentMask::Health;

void healthSystemRegisterEntity(Scene* scene, int id)
{
    EventQueue::get().registerCallback(Event::DamageEntity, id,
    [=](const Event& event, int entity)
    {
        HealthComp* hp = scene->getHealth(entity);
        hp->hp--;
        if (hp->hp < 0) hp->hp = 0;
    });
}

static void execute(Scene* scene, int id)
{
    HealthComp* hc = scene->getHealth(id);

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

void healthSystemUpdate(Scene* scene)
{
    for (int i = 0; i < scene->m_entities.size(); i++)
    {
        if (!scene->m_entities[i]) continue;

        if ((scene->m_entities[i]->mask & signature) == signature)
            execute(scene, i);
    }
}