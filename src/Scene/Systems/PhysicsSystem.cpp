#include "Scene/Systems.hpp"
#include "Scene/Scene.hpp"

static constexpr int signature = (int)ComponentMask::RigidBody;

static void execute(Scene* scene, int id)
{
    RigidBody* rb = scene->getRigidBody(id);
    TransformComp* tr = scene->getTransform(id);

    if (!rb) return;

    tr->pos = rb->getPosition();
}


void physicsSystemUpdate(Scene* scene)
{
    for (int i = 0; i < scene->m_entities.size(); i++)
    {
        if (!scene->m_entities[i]) continue;

        if ((scene->m_entities[i]->mask & signature) == signature)
            execute(scene, i);
    }
}